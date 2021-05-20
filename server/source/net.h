#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#ifndef CHECKMATES_NET_H
#define CHECKMATES_NET_H

#define BOOST_DATE_TIME_NO_LIB

#define TIMEOUT_DELAY 30  // (s)
#define BASIC_DEBUG 1
#define START_GAME_IMITATION 0

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/http/type_traits.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

#include <chrono>
#include <ctime>

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <memory>
#include <thread>

#include <string>
#include <vector>

#include "matcher.h"

namespace beast = boost::beast;          // from <boost/beast.hpp>
namespace http = beast::http;            // from <boost/beast/http.hpp>
namespace websocket = beast::websocket;  // from <boost/beast/websocket.hpp>
namespace asio = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;        // from <boost/asio/ip/tcp.hpp>
using time_point = std::chrono::system_clock::time_point;
namespace fs = std::filesystem;

// global error function
void static fail(beast::error_code ec, char const* what) {
    std::cerr << what << ": " << ec.message() << "\n";
}
// casting windows / linux filepaths
std::string static cast_filepath(const std::string& path) {
    std::string res(path);
#ifdef BOOST_MSVC
    for (auto& c : res)
        if (c == '/')
            c = '\\';
#endif
    return res;
}


// =======================[ Serializer ]=========================


class ISerializer {
public:
    virtual std::string serialize(std::string) = 0;
    virtual std::string deserialize(std::string) = 0;
};

class JSON_serializer: public ISerializer {
public:
    std::string serialize(std::string) override;
    std::string deserialize(std::string) override;
};


// =======================[ Logger ]=========================

class Session;

class ILogger {
public:
    virtual void log(const std::string& data) = 0;
    virtual void set_log_file(const std::string& path) = 0;
    virtual void close() = 0;
    virtual void init(beast::error_code& ec) = 0;
};

class FileLogger : public ILogger {
public:
    FileLogger(std::shared_ptr<std::string const> const& log_dir)
        : log_dir_(log_dir)
    {
        dir_ = fs::path(*log_dir_);
    }

    void log(const std::string& data) override;
    void set_log_file(const std::string& path) override { dir_ = fs::path(path); }
    void init(beast::error_code& ec) override;
    void close() override;
    bool is_initialized() { return initialized; }

private:

    std::string serializeTimePoint(const time_point& time, const std::string& format);

    std::shared_ptr<std::string const> const& log_dir_;
    std::ofstream log_stream_;
    fs::path dir_;
    bool initialized = false;
};


// =======================[ Protocol Specific Handlers ]=========================

class IFormat {
public:
    //void handle_request(beast::string_view doc_root, http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send) {
    //template<bool isRequest, class Body, class Fields>
    //void operator()(http::message<isRequest, Body, Fields>&& msg) const

    // This function produces an HTTP response for the given
    // request. The type of the response object depends on the
    // contents of the request, so the interface requires the
    // caller to pass a generic lambda for receiving the response.

    virtual void handle_request(beast::string_view
        , http::request<http::string_body>&&
        , const std::shared_ptr<ILogger>& logger
        , std::function<void(http::message<false, http::string_body, http::fields>)>
        , Session&
    ) = 0;
};


// =======================[ Session ]=========================


// Handles an HTTP / WS server connection
class Session : public std::enable_shared_from_this<Session>
{
    // This is the C++11 equivalent of a generic lambda.
    // The function object is used to send an HTTP message.
    struct send_lambda
    {
        Session& self_;

        explicit
            send_lambda(Session& self)
            : self_(self)
        {
        }

        void  operator()(http::message<false, http::string_body, http::fields>&& msg) const
        {
            // The lifetime of the message has to extend
            // for the duration of the async operation so
            // we use a shared_ptr to manage it.
            auto sp = std::make_shared<
                http::message<false, http::string_body, http::fields>>(std::move(msg));

        // Store a type-erased version of the shared
        // pointer in the class to keep it alive.
            self_.res_ = sp;

            // Write the response
            http::async_write(
                self_.stream_,
                *sp,
                beast::bind_front_handler(
                    &Session::on_write,
                    self_.shared_from_this(),
                    sp->need_eof()));
        }
    };

    beast::tcp_stream stream_;
    beast::flat_buffer buffer_;
    std::shared_ptr<std::string const> doc_root_;
    http::request<http::string_body> req_;
    std::shared_ptr<void> res_;
    std::shared_ptr<IFormat> format_;
    send_lambda lambda_;
    const std::shared_ptr<ILogger> logger_;

public:
    size_t token = 0;
    std::shared_ptr<IUser> user = nullptr;

    Session(
        tcp::socket&& socket,
        std::shared_ptr<std::string const> const& doc_root,
        std::shared_ptr<std::string const> const& log_dir,
        std::shared_ptr<IFormat>& format
    )
        : stream_(std::move(socket))
        , doc_root_(doc_root)
        , logger_(std::make_shared<FileLogger>(log_dir))
        , format_(format)
        , lambda_(*this)
    {
    }

    //TEST
    //(std::string) {
    //
    //}

    // Start the asynchronous operation
    void run() {
        if (BASIC_DEBUG) std::cout << "session run\n";
        beast::error_code ec;
        logger_->init(ec);
        if (ec)
            fail(ec, "unable to init log");
        else
            // TODO: пробросить какой-нибудь айпи или типа
            logger_->log("Connected\n");

        // We need to be executing within a strand to perform async operations
        // on the I/O objects in this session. Although not strictly necessary
        // for single-threaded contexts, this example code is written to be
        // thread-safe by default.
        asio::dispatch(stream_.get_executor(),
            beast::bind_front_handler(
                &Session::do_read,
                shared_from_this()));
    }

    void do_read() {
        if (BASIC_DEBUG) std::cout << "do read\n";
        // Make the request empty before reading,
        // otherwise the operation behavior is undefined.
        req_ = {};

        // Set the timeout.
        stream_.expires_after(std::chrono::seconds(TIMEOUT_DELAY));

        // Read a request
        http::async_read(stream_, buffer_, req_,
            beast::bind_front_handler(
                &Session::on_read,
                shared_from_this()));
    }

    void on_read(beast::error_code ec, std::size_t bytes_transferred) {
        if (BASIC_DEBUG) std::cout << "on read\n";
        boost::ignore_unused(bytes_transferred);
        // This means they closed the connection
        std::string logging_data;
        if (ec == http::error::end_of_stream) {
            logger_->log("Connection refused by client\n");
            return do_close();
        }

        if (ec) {
            logger_->log("Read failed: " + ec.message() + '\n');
            return fail(ec, "read");
        }

        // Send the response
        format_->handle_request(*doc_root_, std::move(req_), logger_, lambda_, *this);
    }

    void on_write(bool close, beast::error_code ec, std::size_t bytes_transferred) {
        if (BASIC_DEBUG) std::cout << "on write\n";
        boost::ignore_unused(bytes_transferred);

        if (ec) {
            logger_->log("Write failed: " + ec.message() + '\n');
            return fail(ec, "write");
        }

        if (close)
        {
            // This means we should close the connection, usually because
            // the response indicated the "Connection: close" semantic.
            return do_close();
        }

        // We're done with the response so delete it
        res_ = nullptr;

        // Read another request
        do_read();
    }

    void do_close() {
        if (BASIC_DEBUG) std::cout << "do close\n";
        // Send a TCP shutdown
        logger_->log("Connection closed successfully\n");
        beast::error_code ec;
        stream_.socket().shutdown(tcp::socket::shutdown_send, ec);

        // At this point the connection is closed gracefully
    }
};

class WebSocketSession : public std::enable_shared_from_this<WebSocketSession>
{
    struct send_lambda
    {
        WebSocketSession& self_;

        explicit
            send_lambda(WebSocketSession& self)
            : self_(self)
        {
        }

        void operator()(http::message<false, http::string_body, http::fields>&& msg) const
        {
            std::cout << "ws: send\n";
        }
    };

    beast::flat_buffer buffer_;
    std::shared_ptr<std::string const> doc_root_;
    std::shared_ptr<IFormat> format_;
    send_lambda lambda_;
    const std::shared_ptr<ILogger> logger_;
    websocket::stream<beast::tcp_stream> stream_;
    //beast::tcp_stream stream_;

public:
    // Take ownership of the socket

    WebSocketSession(
        tcp::socket&& socket,
        std::shared_ptr<std::string const> const& doc_root,
        std::shared_ptr<std::string const> const& log_dir,
        std::shared_ptr<IFormat>& format
    )
        : stream_(std::move(socket))
        , doc_root_(doc_root)
        , logger_(std::make_shared<FileLogger>(log_dir))
        , format_(format)
        , lambda_(*this)
    {
    }
    // Get on the correct executor
    void run()
    {
        // We need to be executing within a strand to perform async operations
        // on the I/O objects in this session. Although not strictly necessary
        // for single-threaded contexts, this example code is written to be
        // thread-safe by default.
        asio::dispatch(stream_.get_executor(),
            beast::bind_front_handler(
                &WebSocketSession::on_run,
                shared_from_this()));
    }

    // Start the asynchronous operation
    void  on_run()
    {
        // Set suggested timeout settings for the websocket
        stream_.set_option(
            websocket::stream_base::timeout::suggested(
                beast::role_type::server));

        // Set a decorator to change the Server of the handshake
        stream_.set_option(websocket::stream_base::decorator(
            [](websocket::response_type& res)
            {
                res.set(http::field::server,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                    " websocket-server-async");
            }));
        // Accept the websocket handshake
        stream_.async_accept(
            beast::bind_front_handler(
                &WebSocketSession::on_accept,
                shared_from_this()));
    }

    void on_accept(beast::error_code ec)
    {
        if (ec)
            return fail(ec, "accept");

        // Read a message
        do_read();
    }

    void  do_read()
    {
        // Read a message into our buffer
        stream_.async_read(
            buffer_,
            beast::bind_front_handler(
                &WebSocketSession::on_read,
                shared_from_this()));
    }

    void    on_read(
            beast::error_code ec,
            std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        // This indicates that the session was closed
        if (ec == websocket::error::closed)
            return;

        if (ec)
            fail(ec, "read");

        // Echo the message
        //std::string* recieved = (std::string*)buffer_.data().data();
        //std::string msg = "WS Echo: " + *recieved;
        //auto msg = asio::buffer(std::string("WS Echo: "));
        stream_.text(stream_.got_text());
        stream_.async_write(
            buffer_.data(),
            //asio::buffer(msg),
                beast::bind_front_handler(
                &WebSocketSession::on_write,
                shared_from_this()));
    }

    void on_write(
            beast::error_code ec,
            std::size_t bytes_transferred)
    {
        boost::ignore_unused(bytes_transferred);

        if (ec)
            return fail(ec, "write");

        // Clear the buffer
        buffer_.consume(buffer_.size());

        // Do another read
        do_read();
    }
};


// =======================[ WS ]=========================


class WS_format : public IFormat {
public:
    WS_format() = delete;
    WS_format(const std::shared_ptr<ISerializer>& serializer, std::shared_ptr<IMatcherQueue> matcher_queue)
        : serializer_(serializer)
        , mq_(matcher_queue)
    {
    }

    void game_request_handler();
    void game_response_handler();
    void chat_handler();

    virtual void handle_request(beast::string_view doc_root
        , http::request<http::string_body>&& req
        , const std::shared_ptr<ILogger>& logger
        , std::function<void(http::message<false, http::string_body, http::fields>)> send
        , Session& session
    ) override {
        std::cout << "WS format handler" << std::endl;
    }
    

private:
    std::shared_ptr<ISerializer> serializer_;
    std::shared_ptr<IMatcherQueue> mq_;
    const std::string type = "ws";
};


// =======================[ HTTP ]=========================

class HTTP_format: public IFormat {
public:

    HTTP_format() = delete;
    HTTP_format(const std::shared_ptr<ISerializer>& serializer, std::shared_ptr<IMatcherQueue> matcher_queue)
        : serializer_(serializer) 
        , mq_(matcher_queue)
    {
    }

    void handle_request(beast::string_view doc_root
        , http::request<http::string_body>&& req
        , const std::shared_ptr<ILogger>& logger
        , std::function<void(http::message<false, http::string_body, http::fields>)> send
        , Session& session
    ) override {
        std::cout << "HTTP-handler: Got an request!" << std::endl;
        std::string logging_data;
        // Returns a bad request response
        auto const bad_request =
            [&req](beast::string_view why)
        {
            http::response<http::string_body> res{ http::status::bad_request, req.version() };
            res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(http::field::content_type, "text/html");
            res.keep_alive(req.keep_alive());
            res.body() = std::string(why);
            res.prepare_payload();
            return res;
        };

        // Returns a not found response
        auto const not_found =
            [&req](beast::string_view target)
        {
            http::response<http::string_body> res{ http::status::not_found, req.version() };
            res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(http::field::content_type, "text/html");
            res.keep_alive(req.keep_alive());
            res.body() = "The resource '" + std::string(target) + "' was not found.";
            res.prepare_payload();
            return res;
        };

        // Returns a server error response
        auto const server_error =
            [&req](beast::string_view what)
        {
            http::response<http::string_body> res{ http::status::internal_server_error, req.version() };
            res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(http::field::content_type, "text/html");
            res.keep_alive(req.keep_alive());
            res.body() = "An error occurred: '" + std::string(what) + "'";
            res.prepare_payload();
            return res;
        };

        //
        // CHECKS AND VALIDATION
        //

        // Make sure we can handle the method
        if (req.method() != http::verb::get &&
            req.method() != http::verb::head &&
            req.method() != http::verb::post) {
            logger->log(logging_data += "fail: unsupported request: " + req.method_string().to_string());
            return send(bad_request("Unknown HTTP-method"));
        }
        // Request path must be absolute and not contain "..".
        if (req.target().empty() ||
            req.target()[0] != '/' ||
            req.target().find("..") != beast::string_view::npos) {
            logger->log(logging_data += "fail: invalid target: " + req.method_string().to_string());
            return send(bad_request("Illegal request-target"));
        }
        // Build the path to the requested file
        std::string path = path_cat(doc_root, req.target());
        if (req.target().back() == '/')
            path.append("index.html");

        //
        // REQUEST EXECUTION
        //

        beast::error_code ec;
        http::file_body::value_type body;
        http::string_body::value_type string_body;

        logging_data += req.method_string().to_string() + "-req file: " + req.target().to_string() + "\n";

        if (req.method() == http::verb::post) {
            // go to DB write data
        }
        else {
            // Attempt to open the file
            body.open(path.c_str(), beast::file_mode::scan, ec);

            // Handle the case where the file doesn't exist
            if (ec == beast::errc::no_such_file_or_directory) {
                logger->log(logging_data += "fail: unreachable target: " + req.target().to_string());
                return send(not_found(req.target()));
            }

            // Handle an unknown error
            if (ec) {
                logger->log(logging_data += "fail: unknown error: " + ec.message());
                return send(server_error(ec.message()));
            }

            // Cache the size since we need it after the move
            auto size = body.size();

            // Respond to HEAD request
            if (req.method() == http::verb::head)
            {
                http::response<http::string_body> res{ http::status::ok, req.version() };
                res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
                res.set(http::field::content_type, mime_type(path));
                res.content_length(size);
                res.keep_alive(req.keep_alive());
                logger->log(logging_data += "OK");
                return send(std::move(res));
            }

            // Respond to GET request

            /*template<
                bool isRequest,             // `true` for requests, `false` for responses
                class Body,                 // Controls the container and algorithms used for the body
                class Fields = fields>      // The type of container to store the fields
                class message;

             Construct a message.

                @param body_args A tuple forwarded as a parameter
                pack to the body constructor.

                @param fields_args A tuple forwarded as a parameter
                pack to the `Fields` constructor.

                template<class... BodyArgs, class... FieldsArgs>
                message(std::piecewise_construct_t,
                    std::tuple<BodyArgs...> body_args,
                    std::tuple<FieldsArgs...> fields_args);
            */


            http::response<http::file_body> res_file{
                std::piecewise_construct,
                std::make_tuple(std::move(body)),
                std::make_tuple(http::status::ok, req.version())      // тапл - это кортеж - контейнер из произвольного числа элементов произвольного типа
            };

            size_t bytes_read = 1;
            std::string content;

            char* block = new char [1024];
            while (bytes_read) {
                bytes_read = res_file.body().file().read(block, 1024, ec);
                if (ec) {
                    fail(ec, "file copy");
                    logging_data += "an error occured while copying " + req.target().to_string() + ": " + ec.message() + "\n"
                        + "here: " + std::string(block, bytes_read) + '\n';

                }
                std::string block_string(block, bytes_read);
                content += block_string;
            }
            delete[] block;

            if (START_GAME_IMITATION) {
                if (!session.user) {
                    // TODO send message unauthorised
                    std::cout << "unauthorised\n";
                    session.user = std::make_shared<User>(send);
                    session.user->get_info();
                    mq_->push_user(session.user);
                }
                content = "Game start:\nplayers: Player1, Player2\n";
                size = content.size();
            }
            
            http::response<http::string_body> res{
                std::piecewise_construct,
                std::make_tuple(content),
                std::make_tuple(http::status::ok, req.version())
            };

            res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(http::field::content_type, mime_type(path));
            res.content_length(size);
            res.keep_alive(req.keep_alive());
            logger->log(logging_data += "OK\nCreating a response of " + std::to_string(size) + " bytes\n");
            return send(std::move(res));
        }
        // TODO: common value res
        //return send(std::move(res));
    }

private:

    beast::string_view mime_type(beast::string_view path) {
        using beast::iequals;
        auto const ext = [&path]
        {
            auto const pos = path.rfind(".");
            if (pos == beast::string_view::npos)
                return beast::string_view{};
            return path.substr(pos);
        }();
        if (iequals(ext, ".htm"))  return "text/html";
        if (iequals(ext, ".html")) return "text/html";
        if (iequals(ext, ".php"))  return "text/html";
        if (iequals(ext, ".css"))  return "text/css";
        if (iequals(ext, ".txt"))  return "text/plain";
        if (iequals(ext, ".js"))   return "application/javascript";
        if (iequals(ext, ".json")) return "application/json";
        if (iequals(ext, ".xml"))  return "application/xml";
        if (iequals(ext, ".swf"))  return "application/x-shockwave-flash";
        if (iequals(ext, ".flv"))  return "video/x-flv";
        if (iequals(ext, ".png"))  return "image/png";
        if (iequals(ext, ".jpe"))  return "image/jpeg";
        if (iequals(ext, ".jpeg")) return "image/jpeg";
        if (iequals(ext, ".jpg"))  return "image/jpeg";
        if (iequals(ext, ".gif"))  return "image/gif";
        if (iequals(ext, ".bmp"))  return "image/bmp";
        if (iequals(ext, ".ico"))  return "image/vnd.microsoft.icon";
        if (iequals(ext, ".tiff")) return "image/tiff";
        if (iequals(ext, ".tif"))  return "image/tiff";
        if (iequals(ext, ".svg"))  return "image/svg+xml";
        if (iequals(ext, ".svgz")) return "image/svg+xml";
        return "application/text";
    }

    // Append an HTTP rel-path to a local filesystem path.
    // The returned path is normalized for the platform.
    std::string path_cat(beast::string_view base, beast::string_view path) {
        if (base.empty())
            return std::string(path);
        std::string result(base);
#ifdef BOOST_MSVC
        char constexpr path_separator = '\\';
        if (result.back() == path_separator)
            result.resize(result.size() - 1);
        result.append(path.data(), path.size());
        for (auto& c : result)
            if (c == '/')
                c = path_separator;
#else
        char constexpr path_separator = '/';
        if (result.back() == path_separator)
            result.resize(result.size() - 1);
        result.append(path.data(), path.size());
#endif
        return result;
    }

    void authorize_handler();
    void register_handler();

    std::shared_ptr<ISerializer> serializer_;
    std::shared_ptr<IMatcherQueue> mq_;
    const std::string type = "http";
};


#endif //CHECKMATES_NET_H

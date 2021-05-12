#ifndef CHECKMATES_NET_H
#define CHECKMATES_NET_H

#define TIMEOUT_DELAY 30  // (s)

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#define BOOST_DATE_TIME_NO_LIB

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace asio = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

//#include "matcher.h"

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <vector>

// ���������� ������� ������ ������
void static fail(beast::error_code ec, char const* what) {
    std::cerr << what << ": " << ec.message() << "\n";
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


class ILogger {
public:
    virtual void log(std::string data) = 0;
};

class ConsoleLogger : ILogger {
public:
    void log(std::string data) override;
};

// =======================[ Protocol Specific Handlers ]=========================

class IFormat {
public:
    template <class Body, class Allocator, class Send>
    void handle_request(beast::string_view, http::request<Body, http::basic_fields<Allocator>>&&, Send&&) {
        std::cout << "basic to override\n";
    }
};

// =======================[ WS ]=========================


//template <typename Serializer>
class WS_format /*: public IFormat*/{
public:
    WS_format() = delete;
    WS_format(ISerializer* serializer)
    : serializer_(serializer)
    {
    }

    void game_request_handler();
    void game_response_handler();
    void chat_handler();

    template <class Body, class Allocator, class Send>
    void handle_request(beast::string_view doc_root, http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send) {
        std::cout << "smtg\n";
    }
private:
    ISerializer* serializer_;
};


// =======================[ HTTP ]=========================


//template <typename Serializer/*, typename HTTP_Logger*/>
class HTTP_format: public IFormat {
public:

    HTTP_format() = delete;
    //HTTP_format(std::shared_ptr<ISerializer> serializer)
    HTTP_format(ISerializer* serializer)
        //: serializer_(std::make_shared<ISerializer>(serializer))
        : serializer_(serializer)
    {
    }

    // client
    // void get_handler();
    // void post_handler();

    // server
    void authorize_handler();
    void register_handler();

    // This function produces an HTTP response for the given
    // request. The type of the response object depends on the
    // contents of the request, so the interface requires the
    // caller to pass a generic lambda for receiving the response.
    template <class Body, class Allocator, class Send>
    void handle_request(beast::string_view doc_root, http::request<Body, http::basic_fields<Allocator>>&& req, Send&& send) {
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
            req.method() != http::verb::post)
            return send(bad_request("Unknown HTTP-method"));

        // Request path must be absolute and not contain "..".
        if (req.target().empty() ||
            req.target()[0] != '/' ||
            req.target().find("..") != beast::string_view::npos)
            return send(bad_request("Illegal request-target"));

        // Build the path to the requested file
        std::string path = path_cat(doc_root, req.target());
        if (req.target().back() == '/')
            path.append("index.html");

        //
        // REQUEST EXECUTION
        // 
        
        if (req.method() == http::verb::post) {
            // go to DB write data
        }
        else {

            // Attempt to open the file
            beast::error_code ec;
            http::file_body::value_type body;
            body.open(path.c_str(), beast::file_mode::scan, ec);

            // Handle the case where the file doesn't exist
            if (ec == beast::errc::no_such_file_or_directory)
                return send(not_found(req.target()));

            // Handle an unknown error
            if (ec)
                return send(server_error(ec.message()));

            // Cache the size since we need it after the move
            auto const size = body.size();

            // Respond to HEAD request
            if (req.method() == http::verb::head)
            {
                http::response<http::empty_body> res{ http::status::ok, req.version() };
                res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
                res.set(http::field::content_type, mime_type(path));
                res.content_length(size);
                res.keep_alive(req.keep_alive());
                return send(std::move(res));
            }

            // Respond to GET request

            /*template<
                bool isRequest,             // `true` for requests, `false` for responses
                class Body,                 // Controls the container and algorithms used for the body
                class Fields = fields>      // The type of container to store the fields
                class message;

            /* Construct a message.

                @param body_args A tuple forwarded as a parameter
                pack to the body constructor.

                @param fields_args A tuple forwarded as a parameter
                pack to the `Fields` constructor.

                template<class... BodyArgs, class... FieldsArgs>
                message(std::piecewise_construct_t,
                    std::tuple<BodyArgs...> body_args,
                    std::tuple<FieldsArgs...> fields_args);
            */
            http::response<http::file_body> res{
                std::piecewise_construct,
                std::make_tuple(std::move(body)),
                std::make_tuple(http::status::ok, req.version())      // тапл - это кортеж - контейнер из произвольного числа элементов произвольного типа
            };
            res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(http::field::content_type, mime_type(path));
            res.content_length(size);
            res.keep_alive(req.keep_alive());
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

    //std::shared_ptr<ISerializer> serializer_;
    ISerializer* serializer_;
};


// =======================[ Session ]=========================


// ������ Net
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

        template<bool isRequest, class Body, class Fields>
        void
            operator()(http::message<isRequest, Body, Fields>&& msg) const
        {
            // The lifetime of the message has to extend
            // for the duration of the async operation so
            // we use a shared_ptr to manage it.
            auto sp = std::make_shared<
                http::message<isRequest, Body, Fields>>(std::move(msg));

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
    IFormat* format_;
    ISerializer* js_;
    //HTTP_format* format_;
    send_lambda lambda_;

public:
    // Take ownership of the stream
    // TODO: ������� http / ws ������� ���������
    Session(
        tcp::socket&& socket,
        std::shared_ptr<std::string const> const& doc_root,
        IFormat* format)
        : stream_(std::move(socket))
        , doc_root_(doc_root)
        /*, format_(format)*/
        , lambda_(*this)
    {
        js_ = new JSON_serializer();
        format_ = new HTTP_format(js_);
    }

    // Start the asynchronous operation
    void run() {
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
        // Make the request empty before reading,
        // otherwise the operation behavior is undefined.
        req_ = {};

        // Set the timeout.
        stream_.expires_after(std::chrono::seconds(30));

        // Read a request
        http::async_read(stream_, buffer_, req_,
            beast::bind_front_handler(
                &Session::on_read,
                shared_from_this()));
    }

    void on_read(beast::error_code ec, std::size_t bytes_transferred) {
        boost::ignore_unused(bytes_transferred);

        // This means they closed the connection
        if (ec == http::error::end_of_stream)
            return do_close();

        if (ec)
            return fail(ec, "read");

        // Send the response
        format_->handle_request(*doc_root_, std::move(req_), lambda_);
    }

    void on_write(bool close, beast::error_code ec, std::size_t bytes_transferred) {
        boost::ignore_unused(bytes_transferred);

        if (ec)
            return fail(ec, "write");

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
        // Send a TCP shutdown
        beast::error_code ec;
        stream_.socket().shutdown(tcp::socket::shutdown_send, ec);

        // At this point the connection is closed gracefully
    }
};
#endif //CHECKMATES_NET_H
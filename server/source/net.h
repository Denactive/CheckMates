#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#define BOOST_DATE_TIME_NO_LIB

#ifndef CHECKMATES_NET_H
#define CHECKMATES_NET_H

#define TIMEOUT_DELAY 30  // (s)
#define COOKIE_LIFETIME 15
#define THREADS_NUM 1

#define BASIC_DEBUG 1
#define BASIC_DEBUG_WS 1
#define START_GAME_IMITATION 1
/*
1 4 3 4
6 4 4 4
0 5 3 2
7 1 5 2
0 3 4 7
7 6 5 5
4 7 6 5
*/
#define REGESTRY_IMITATION 1
#define MOVE_PARSE_DEBUG 1

// comment this
#define ONLINE_GAME_IMITATION

#define START_GAME_RESPONSE \
"{\n\
  game_token: %s,\n\
  uid: %zu,\n\
  side: %s,\n\
  opponent:\n  {\n    name: %s,\n    rating: %s,\n    avatar: %s\n  }\n\
}"

#define MOVE_RESPONSE \
"{\n\
  available moves: %s,\n\
  Ginfo:\n  {\n    isPlayer: %d,\n    isGame: %d,\n    isVictory: %d,\n    isCheck: %d,\n  prev: %d,\n cur: %d,\n}\n\
}"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/http/type_traits.hpp>
#include <boost/asio/dispatch.hpp>
#include <boost/asio/strand.hpp>
#include <boost/config.hpp>
#include <boost/format.hpp>

#include <iostream>
#include <sstream>
#include <fstream>
#include <filesystem>

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <memory>
#include <thread>
#include <sstream>
#include <string>
#include <vector>

#include "matcher.h"

namespace beast = boost::beast;          // from <boost/beast.hpp>
namespace http = beast::http;            // from <boost/beast/http.hpp>
namespace websocket = beast::websocket;  // from <boost/beast/websocket.hpp>
namespace asio = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;        // from <boost/asio/ip/tcp.hpp>
namespace fs = std::filesystem;

class ioc_Singleton
{
public:
    static ioc_Singleton& instance()
    {
        static ioc_Singleton singleton;
        return singleton;
    }

    asio::io_context& get() { return ioc_; }

    // Other non-static member functions
private:
    ioc_Singleton() {}                                  // Private constructor
    ~ioc_Singleton() {}
    ioc_Singleton(const ioc_Singleton&);                 // Prevent copy-construction
    ioc_Singleton& operator=(const ioc_Singleton&);      // Prevent assignment
    asio::io_context ioc_{ THREADS_NUM };
};

class MQSingleton
{
public:
    static MQSingleton& instance()
    {
        static MQSingleton singleton;
        return singleton;
    }

    MatcherQueue& get() { return mq; }

    // Other non-static member functions
private:
    MQSingleton() {}
    ~MQSingleton() {}
    MQSingleton(const MQSingleton&);
    MQSingleton& operator=(const MQSingleton&);
    MatcherQueue mq;
};

class Session;

class SessionsSingleton
{
public:
    static SessionsSingleton& instance()
    {
        static SessionsSingleton singleton;
        return singleton;
    }

    std::map<std::string, std::shared_ptr<Session>, StringTokenComparator>& get() { return session_map; }

    // Other non-static member functions
private:
    SessionsSingleton() {}
    ~SessionsSingleton() {}
    SessionsSingleton(const SessionsSingleton&);
    SessionsSingleton& operator=(const SessionsSingleton&);
    std::map<std::string, std::shared_ptr<Session>, StringTokenComparator> session_map;
};

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

    //std::string serializeTimePoint(const time_point& time, const std::string& format);

    std::shared_ptr<std::string const> const& log_dir_;
    std::ofstream log_stream_;
    fs::path dir_;
    bool initialized = false;
};


// =======================[ Protocol Specific Handlers ]=========================


// ===================================[ HTTP ]===================================


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
    MatcherQueue& mq_;
    send_lambda lambda_;
    const std::shared_ptr<ILogger> logger_;

public:
    size_t token = 0;
    std::shared_ptr<IUser> user = nullptr;
    std::shared_ptr<UserMap>& active_users_;

    Session(
        tcp::socket&& socket,
        std::shared_ptr<std::string const> const& doc_root,
        std::shared_ptr<std::string const> const& log_dir,
        std::shared_ptr<UserMap>& active_users
    )
        : stream_(std::move(socket))
        , doc_root_(doc_root)
        , logger_(std::make_shared<FileLogger>(log_dir))
        , mq_(MQSingleton::instance().get())
        , active_users_(active_users)
        , lambda_(*this)
    {
    }

    void start_cookie_timer(Cookie c, int value) {
        if (BASIC_DEBUG) std::cout << "start cookie timer\n";
        auto cookie_timer = std::make_shared<asio::steady_timer>(ioc_Singleton::instance().get(), std::chrono::seconds{ value });
        auto active_users = active_users_;
        cookie_timer->async_wait([cookie_timer, c, value, active_users](const boost::system::error_code& ec) mutable {
            std::cout << value << " seconds passed";
            if (ec)
                std::cout << " | errors: " << ec.message() << std::endl;
            else
                std::cout << '\n';

            auto cookie = serializeTimePoint(c);
            std::cout << "Cookie " << cookie << " is not active more\n";

            auto search = active_users->find(cookie);
            if (search != active_users->end()) {
                std::cout << "User = { token: " << search->first << ", name: " << search->second->get_nickname() << " } has been deleted from the user map" << '\n';
                active_users->erase(search);
            }
            else {
                std::cout << "Cookie " << cookie << " not found in the active users map\n";
            }
        });
    }

    void on_queue(std::string&& logging_data, const std::shared_ptr<ILogger>& logger, unsigned short version) {
        auto const error_res = [&version, &logger](std::string msg) {
            http::response<http::string_body> res{
            std::piecewise_construct,
            std::make_tuple(msg),
            std::make_tuple(http::status::ok, version)
            };

            res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(http::field::content_type, "text/html");
            res.content_length(msg.size());
            res.keep_alive(true);
            res.prepare_payload();
            logger->log("ERROR\nCreating an response of " + std::to_string(msg.size()) + " bytes:\n\n" + msg + "\n\n");
            return res;
        };

        if (BASIC_DEBUG) std::cout << "on queue | Session-Timer set to 2 minutes\n";
        logger->log(logging_data);

        stream_.expires_after(std::chrono::minutes{ 2 });
        auto push_result = mq_.push_user(user);

        if (push_result != nullptr) {
            // если запушили и для него сразу нашелся оппонент
            /*
            game_token:% s, \
            uid : % zu, \
            side : % s\
            opponent : { name:% s, rating : % s, avatar : % s }*/
            bool is_first_white = false;
            if (push_result->wPlayer->get_user()->get_token() == user->get_token())
                is_first_white = true;

            auto opponent = is_first_white ? push_result->bPlayer->get_user() : push_result->wPlayer->get_user();

            // message to opponent
        std::string content = (boost::format(START_GAME_RESPONSE)
                % push_result->get_token_string()
                % opponent->get_id()
                % (!is_first_white ? "white" : "black")
                % user->get_nickname()
                % user->get_rating()
                % user->get_avatar()
                ).str();

            auto opponent_session = SessionsSingleton::instance().get().find(opponent->get_token_string());
            if (opponent_session == SessionsSingleton::instance().get().end()) {
                std::cout << "failed to get the opponent session!\n";
                lambda_(error_res("failed to get the opponent session\n"));
            }

            http::response<http::string_body> res_to_opponent{
                std::piecewise_construct,
                std::make_tuple(content),
                std::make_tuple(http::status::ok, version)
            };
            res_to_opponent.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            res_to_opponent.set(http::field::content_type, "application/json");
            res_to_opponent.content_length(content.size());
            res_to_opponent.keep_alive(true);
            logger->log("Creating a response to opponent: " + opponent->get_token_string() + " of " + std::to_string(content.size()) + " bytes:\n\n" + content + "\n\n");
            // send
            opponent_session->second->lambda_(std::move(res_to_opponent));

            // message to current user
            content = (boost::format(START_GAME_RESPONSE)
                % push_result->get_token_string()
                % user->get_id() 
                % (is_first_white ? "white" : "black")
                % opponent->get_nickname()
                % opponent->get_rating()
                % opponent->get_avatar()
            ).str();
            
            http::response<http::string_body> res{
                std::piecewise_construct,
                std::make_tuple(content),
                std::make_tuple(http::status::ok, version)
            };

            res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(http::field::content_type, "application/json");
            res.content_length(content.size());
            res.keep_alive(true);
            logger->log("OK\nCreating a response to this player: " + user->get_token_string() + " of " + std::to_string(content.size()) + " bytes:\n\n" + content + "\n\n");
            // send
            return lambda_(std::move(res));
        }
        else {
            // save session to hold the connection until the opponent apearance
            const auto [item, success] = SessionsSingleton::instance().get().insert({ user->get_token_string(), shared_from_this() });
            if (success) {
                logger->log("User № " + item->first + " is placed to the matching queue\n");
                logger->close();
            }
            else {
                logger->log("An error occured while putting User № " + user->get_token_string() + " to the matching queue. The Session will be aborted\n");
                return lambda_(error_res("Fail to add to the matcher queue\n"));
            }
        }
    }

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
        handle_request(std::move(req_));
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

    void handle_request(http::request<http::string_body>&& req) {
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
            logger_->log(logging_data += "fail: unsupported request: " + req.method_string().to_string());
            return lambda_(bad_request("Unknown HTTP-method"));
        }
        // Request path must be absolute and not contain "..".
        if (req.target().empty() ||
            req.target()[0] != '/' ||
            req.target().find("..") != beast::string_view::npos) {
            logger_->log(logging_data += "fail: invalid target: " + req.method_string().to_string());
            return lambda_(bad_request("Illegal request-target"));
        }
        // Build the path to the requested file
        std::string path = path_cat(*doc_root_, req.target());
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
                logger_->log(logging_data += "fail: unreachable target: " + req.target().to_string());
                return lambda_(not_found(req.target()));
            }

            // Handle an unknown error
            if (ec) {
                logger_->log(logging_data += "fail: unknown error: " + ec.message());
                return lambda_(server_error(ec.message()));
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
                logger_->log(logging_data += "OK");
                return lambda_(std::move(res));
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

            char* block = new char[1024];
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
            if (REGESTRY_IMITATION) {
                user = std::make_shared<User>();
                std::cout << "user №" << serializeTimePoint(user->get_token(), "%y-%m-%d-%H_%M_%S") << ' ';

                const auto [active_user, success] = active_users_->insert({ user->get_token_string(), user });
                if (success)
                    std::cout << "added to the User Map successfully" << std::endl;
                else
                    std::cout << "has not been added to the map | FAIL" << std::endl;

                start_cookie_timer(user->get_token(), COOKIE_LIFETIME);
            }

            if (START_GAME_IMITATION) {
                if (!user) {
                    // TODO send message unauthorised
                    std::cout << "unauthorised\n";
                }
                //auto logging_data_ptr = std::make_shared<std::string>(&logging_data);
                return on_queue(std::move(logging_data), logger_, req.version());
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
            logger_->log(logging_data += "OK\nCreating a response of " + std::to_string(size) + " bytes\n");
            return lambda_(std::move(res));
        }

        // TODO: common value res
        //return send(std::move(res));
    }



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

};


// ====================================[ WS ]====================================


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
    std::string buffer_str_;
    std::shared_ptr<std::string const> doc_root_;
    send_lambda lambda_;
    const std::shared_ptr<ILogger> logger_;
    websocket::stream<beast::tcp_stream> stream_;
    std::string msg = "Hello";

public:
    // Take ownership of the socket

    WebSocketSession(
        tcp::socket&& socket,
        std::shared_ptr<std::string const> const& doc_root,
        std::shared_ptr<std::string const> const& log_dir
    )
        : stream_(std::move(socket))
        , doc_root_(doc_root)
        , logger_(std::make_shared<FileLogger>(log_dir))
        , lambda_(*this)
    {
    }
    // Get on the correct executor
    void run()
    {
        if (BASIC_DEBUG_WS) std::cout << "WS: run\n";
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
        if (BASIC_DEBUG_WS) std::cout << "WS: on run\n";

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
                    " SaberChess websocket-server");
            }));
        // Accept the websocket handshake
        stream_.async_accept(
            beast::bind_front_handler(
                &WebSocketSession::on_accept,
                shared_from_this()));
    }

    void on_accept(beast::error_code ec)
    {
        if (BASIC_DEBUG_WS) std::cout << "WS: on accept\n";
        if (ec)
            return fail(ec, "accept");

        // Read a message
        do_read();
    }

    void  do_read()
    {
        if (BASIC_DEBUG_WS) std::cout << "WS: do read\n";
        // Read a message into our buffer
        stream_.async_read(
            buffer_,
            beast::bind_front_handler(
                &WebSocketSession::on_read,
                shared_from_this()));
    }

    void on_read(
            beast::error_code ec,
            std::size_t bytes_transferred)
    {
        if (BASIC_DEBUG_WS) std::cout << "WS: on read\n";
        boost::ignore_unused(bytes_transferred);

        // This indicates that the session was closed
        if (ec == websocket::error::closed) {
            if (BASIC_DEBUG_WS) std::cout << "WS: client closed connection\n";
            return;
        }

        if (ec)
            fail(ec, "read");

        handle_request();
    }

    void handle_request() {
        auto res = std::make_shared<std::string>();
        auto req = beast::buffers_to_string(buffer_.data());
        if (BASIC_DEBUG_WS) std::cout << "Got an request! : " << req << "\n";

        if (req == "NEED CLOSE") {
            (*res) = "OK | CLOSE";
            return write(res);
        }
        game_error_code ec;
        if (req.find("start")!= std::string::npos) {
            std::cout <<"found start";
            auto game_token = req.find("game_token: ");
            auto comma = req.substr(game_token + 12).find(',');
            auto token = req.substr(game_token + 12, comma);
            if (MOVE_PARSE_DEBUG) std::cout << "\t/game_token:/ " << token << "\n";
            auto uid = req.find("id: ");
            auto a = req.substr(uid + 4).find('}');
            int id = atoi((req.substr(uid + 4, a)+ "\0").c_str());
            if (MOVE_PARSE_DEBUG) std::cout << "\tid: " << id << std::endl;
            std::cout <<"end fuck" <<std::flush;

            auto session = MQSingleton::instance().get();
            auto games = session.get_games();
            auto gamepair = games->find(token);
            auto game = gamepair->second;
            //std::cout << game->send_info().isGame;
            //auto ws = game->you()->Get_Session();
            game->enemy()->Set_Session(shared_from_this());
            std::cout << game->enemy()->Get_Session();
            return;
        }
        std::cout <<"not found start";
        Move m = get_move(req, ec);
        if (ec) {
            print_game_error_code(ec);
            (*res) = game_error_code_to_string(ec);
            return write(res);
        }
        auto session = MQSingleton::instance().get();
        auto games = session.get_games();
        auto gameandtoken = games->find(m.game_token);
        auto game =  gameandtoken->second;
        (*res) = game_error_code_to_string(ec); // OK


        GInfo info = game->send_info();
        int validation = 0;
            if (!validation) {
                game->prepare_turn();
                info = game->send_info();
                std::cout <<"prepare";
            }
            std::array<size_t, 4 >turn;
            turn[0] = m.prev / 8;
            turn[1] = m.prev % 8;
            turn[2] = m.cur / 8;
            turn[3] = m.cur % 8;
            std::cout << turn[0] <<' '<< turn[1]<<' '<< turn[2]<<' ' << turn[3]<<'\n';
            validation = game->run_turn(turn);
            std::cout << validation;
            if (!validation) {
                std::cout << "valid move\n";
            }
            auto you = game->you();
            auto enemy = game->enemy();
            std::vector<std::array<size_t, 4>>avail = you->access();
            if (!validation) {
            game->prepare_turn();
            info = game->send_info();
            std::cout <<"prepare";
            }
            std::stringstream ss;
            ss << "[ ";
            for(std::array<size_t, 4> out : avail) {
                ss << "[ " << out[0]*8 + out[1] << ", "<< out[2]*8 + out[3] << " ], ";
            }
            ss << " ]";
       // available moves: %s,\n\
  //Ginfo:\n  {\n    isPlayer: %d,\n    isGame: %d,\n    isVictory: %d,\n    isCheck: %d,\n  prev: %d,\n cur: %d,\n}\n

            std::string b;
            ss >> b;
  std::string content = (boost::format(MOVE_RESPONSE)
                               //% b.c_str()
                               % ss.str()
                               % info.isPlayer
                               % info.isGame
                               % (int)info.isVictory
                               % info.isCheck
                               % (info.turn[0]* 8 + info.turn[1])
                               % (info.turn[2]* 8 + info.turn[3])
                               ).str();
            *res = content;
            auto ses = game->enemy()->Get_Session();
                    ses->write(res);
    }


    void write(std::shared_ptr<std::string>& res) {
        stream_.text(stream_.got_text());
        stream_.async_write(
            asio::buffer(*res),
            [s = shared_from_this(), res](beast::error_code ec, size_t bytes_transferred) mutable {
            s->on_write(ec, res->size());
        });
    }

    void on_write(
            beast::error_code ec,
            std::size_t bytes_transferred)
    {
        if (BASIC_DEBUG_WS) std::cout << "WS: on write\n";

        boost::ignore_unused(bytes_transferred);

        if (ec)
            return fail(ec, "write");

        // Clear the buffer
        buffer_.consume(buffer_.size());

        // Do another read
        do_read();
    }

    Move get_move(std::string& req, game_error_code& ec) {
        /*
        
        c
        
        { game_token: 21-05-26-00_11_30, uid: 21-05-26-00_11_29, prev: 12, cur: 28 }
        */
        auto print = [](std::string::size_type n, std::string const& s)
        {
            if (n == std::string::npos) {
                std::cout << "not found\n";
            }
            else {
                std::cout << "found: " << s.substr(n) << '\n';
            }
        };

        if (MOVE_PARSE_DEBUG) std::cout << "parsing: " << req << "\n";
        Move m{};

        // game_token: %s,
        auto game_token = req.find("game_token: ");
        //print(game_token, req);
        if (game_token == std::string::npos) {
            ec = game_error_code::no_game_token;
            return m;
        }
        auto comma = req.substr(game_token + 12).find(',');
        //print(comma, req.substr(game_token + 12));
        if (comma == std::string::npos) {
            ec = invalid_format;
            return m;
        }
        //std::cout << "game pos: " << game_token << ", com pos: " << comma << ", res: " <<req.substr(game_token + 12, comma - game_token);
        m.game_token = req.substr(game_token + 12, comma);
        if (MOVE_PARSE_DEBUG) std::cout << "\t/game_token:/ " << m.game_token << "\n";

        // uid: %zu,
        auto uid = req.find("id: ");
        if (uid == std::string::npos) {
            ec = game_error_code::invalid_uid;
            return m;
        }
        comma = req.substr(uid + 4).find(',');
        if (comma == std::string::npos) {
            ec = invalid_format;
            return m;
        }
        m.id = atoi(req.substr(uid + 4, comma - uid).c_str());
        if (MOVE_PARSE_DEBUG) std::cout << "\t/id:/ " << m.id << "\n";


        // prev: %zu,
        auto prev = req.find("prev: ");
        if (prev == std::string::npos) {
            ec = game_error_code::no_prev_move;
            return m;
        }
        comma = req.substr(prev + 6).find(',');
        if (comma == std::string::npos) {
            ec = invalid_format;
            return m;
        }
        m.prev = atoi(req.substr(prev + 6, comma - prev).c_str());
        if (MOVE_PARSE_DEBUG) std::cout << "\t/prev:/ " << m.prev << "\n";

        // cur: %zu,
        auto cur = req.find("cur: ");
        if (cur == std::string::npos) {
            ec = game_error_code::no_cur_move;
            return m;
        }
        comma = req.substr(cur + 5).find(',');
        if (comma == std::string::npos)
            comma = req.substr(cur + 5).find('\n');
        if (comma == std::string::npos)
            comma = req.substr(cur + 5).find('}');
        if (comma == std::string::npos) {
            ec = invalid_format;
            return m;
        }
        m.cur = atoi(req.substr(cur + 5, comma - cur).c_str());
        if (MOVE_PARSE_DEBUG) std::cout << "\t/cur:/ " << m.cur << "\n";
        ec = game_error_code::ok;
        return m;
    }
};
#endif //CHECKMATES_NET_H

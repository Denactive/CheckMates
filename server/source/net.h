#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#define BOOST_DATE_TIME_NO_LIB

#ifndef CHECKMATES_NET_H
#define CHECKMATES_NET_H

#define TIMEOUT_DELAY 300  // (s)
#define COOKIE_LIFETIME 15 // min
#define THREADS_NUM 1

#define BASIC_DEBUG 1
#define BASIC_DEBUG_WS 1
#define START_GAME_IMITATION 1

// test
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
  \"game_token\": \"%s\",\n\
  \"uid\": %zu,\n\
  \"side\": \"%s\",\n\
  \"opponent\":\n  {\n    \"name\": \"%s\",\n    \"rating\": %zu,\n    \"avatar\": \"%s\"\n  }\n\
}"


#define MOVE_RESPONSE \
"{\n\
  \"available moves\": %s,\n\
  \"Ginfo\": {\n\t\t\"isPlayer\": %d,\n\t\t\"isGame\": %d,\n\t\t\"isVictory\": %d,\n\t\t\"isCheck\": %d,\n\t\t\"prev\": %d,\n\t\t\"cur\": %d\n\t}\n\
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

    void start_cookie_timer(Cookie c, int value, unsigned short version, bool keep_alive, std::string& logging_data) {
        if (BASIC_DEBUG) std::cout << "start cookie timer\n";
        auto cookie_timer = std::make_shared<asio::steady_timer>(ioc_Singleton::instance().get(), std::chrono::minutes{ value });
        auto active_users = active_users_;
        
        auto msg = "Cookie: " + serializeTimePoint(c) + "\nCookie is valid for " + std::to_string(value) + " minutes\n";
        http::response<http::string_body> res{
                std::piecewise_construct,
                std::make_tuple(msg),
                std::make_tuple(http::status::ok, version)
        };

        res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        res.set(http::field::content_type, "text/html");
        // Set-Cookie
        res.set(http::field::set_cookie, "token=" + serializeTimePoint(c));
        res.content_length(msg.size());
        res.keep_alive(keep_alive);
        logger_->log(logging_data += "Set-Cookie: token=" + serializeTimePoint(c) + " msg: " + msg + "\nOK\nCreating a response of " + std::to_string(msg.size()) + " bytes\n");
        lambda_(std::move(res));

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
            std::stringstream ss;
            ss << req_.base() << '\n' << req_.body();
            logger_->log("Read failed: " + ec.message() + "\nthe response: " + ss.str());
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

        auto const ok_string_message =
            [&req, &logging_data, sp_log = logger_] (std::string msg)
        {
            http::response<http::string_body> res{
                std::piecewise_construct,
                std::make_tuple(msg),
                std::make_tuple(http::status::ok, req.version())
            };

            res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(http::field::content_type, "text/html");
            res.content_length(msg.size());
            res.keep_alive(req.keep_alive());
            sp_log->log(logging_data += "OK\nCreating a response of " + std::to_string(msg.size()) + " bytes\n");
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

        auto target = req.target().to_string();
        logging_data = target;


        // TODO: check
        auto user_target = target.find("/user/");
        if (user_target != std::string::npos) {
            std::cout << "parse url: user\n";
            std::cout << "\ttarget: " << target << "\n";
            std::cout << "\tfind at: " << user_target << "\n";
            auto uid = atoi(target.substr(user_target + 6).c_str());
            std::cout << "\tuid: " << uid << "\n";
            if (uid == 0)
                return lambda_(bad_request("invalid uid"));
            std::ifstream in((*doc_root_) + "/users.txt");
            if (!in.is_open()) {
                std::cout << "\tfile " << (*doc_root_) + "/users.txt is not oppened\n";
                return lambda_(server_error("invalid uid"));
            }
            std::string users_data;
            char sym = '\0';
            while (in.get(sym) && sym != EOF && sym != '\0')
                users_data += sym;
            users_data += '\0';
            std::cout << "\t\tuser data is:\n" << users_data << "\n\t\ttrying to find a string: '" << "\"uid\": " + std::to_string(uid) <<"'\n";
            auto record_pos = users_data.find("\"uid\": " + std::to_string(uid));
            std::cout << "\t\trecord_pos: " << record_pos << " (" << users_data.substr(record_pos, 10) << "...)" << "\n";
            if (record_pos == std::string::npos) {
                std::cout << "\tnot found | uid\n";
                logger_->log(logging_data += "not found | uid\n");
                return lambda_(not_found("invalid uid"));
            }
            record_pos = users_data.rfind('{', record_pos);
            std::cout << "\t\trecord_pos ('{'): " << record_pos << " (" << users_data.substr(record_pos, 10) << "...)" << "\n";
            if (record_pos == std::string::npos) {
                logger_->log(logging_data += "not found | invalid user record: no '{'\n");
                return lambda_(server_error("invalid user record"));
            }
            auto record_end_pos = users_data.substr(record_pos).find('}');
            std::cout << "\t\trecord_end_pos ('}'): " << record_end_pos << " (" << users_data.substr(record_pos + record_end_pos, 10) << "...)" << "\n";
            if (record_pos == std::string::npos) {
                logger_->log(logging_data += "not found | invalid user record: no '}'\n");
                return lambda_(server_error("invalid user record"));
            }
            auto content = users_data.substr(record_pos, record_end_pos + 1);
            logger_->log("answer:\n" + content);
            return lambda_(ok_string_message(content));
        }

        auto reg_target = target.find("/register/");
        if (reg_target != std::string::npos) {
            std::cout << "parse url: register\n";
            UserInfo user_info{};
            auto name = target.substr(reg_target + 10);
            std::ifstream in((*doc_root_) + "/users.txt");
            if (!in.is_open()) {
                std::cout << "\tfile " << (*doc_root_) + "/users.txt is not oppened\n";
                return lambda_(server_error("invalid uid"));
            }
            std::string users_data;
            char sym = '\0';
            while (in.get(sym) && sym != EOF && sym != '\0')
                users_data += sym;
            
            // name
            auto user_record = users_data.find("\"name\": \"" + name);
            if (user_record == std::string::npos) {
                std::cout << "\t\tno such login: " << name << "\n";
                return lambda_(not_found("no such login"));;
            }
            user_info.nickname = name;

            // whole record
            auto record_pos = users_data.rfind('{', user_record);
            std::cout << "\t\trecord_pos ('{'): " << record_pos << " (" << users_data.substr(record_pos, 10) << "...)" << "\n";
            if (record_pos == std::string::npos) {
                std::cout << "\t\tnot found | invalid user record: no '{'\n";
                logger_->log(logging_data += "not found | invalid user record: no '{'\n");
                return lambda_(server_error("invalid user record"));
            }
            auto record_end_pos = users_data.substr(record_pos).find('}');
            std::cout << "\t\trecord_end_pos ('}'): " << record_end_pos << " (" << users_data.substr(record_pos + record_end_pos, 10) << "...)" << "\n";
            if (record_pos == std::string::npos) {
                std::cout << "\t\tnot found | invalid user record: no '}'\n";
                logger_->log(logging_data += "not found | invalid user record: no '}'\n");
                return lambda_(server_error("invalid user record"));
            }
            auto record = users_data.substr(record_pos, record_end_pos + 1);

            // uid
            auto uid = record.find("\"uid\": ");
            if (uid == std::string::npos) {
                std::cout << "\t\tnot found | invalid user record: no uid\n";
                logger_->log(logging_data += "not found | invalid user record: no uid\n");
                return lambda_(server_error("invalid user record"));
            }
            auto comma = record.substr(uid + 6).find(',');
            if (comma == std::string::npos) {
                std::cout << "\t\tnot found | invalid user record: no comma after uid\n";
                logger_->log(logging_data += "not found | invalid user record: no comma after uid\n");
                return lambda_(server_error("invalid user record"));
            }
            user_info.id = atoi(record.substr(uid + 6, comma).c_str());
            if (user_info.id == 0) {
                std::cout << "\t\tnot found | cannot convert uid\n";
                logger_->log(logging_data += "not found | cannot convert uid\n");
                return lambda_(server_error("invalid user record"));
            }

            // rating
            auto rating = record.find("\"rating\": ");
            if (rating == std::string::npos) {
                std::cout << "\t\tnot found | invalid user record: no rating\n";
                logger_->log(logging_data += "not found | invalid user record: no rating\n");
                return lambda_(server_error("invalid user record"));
            }
            comma = record.substr(rating + 10).find(',');
            if (comma == std::string::npos) {
                std::cout << "\t\tnot found | invalid user record: no comma after rating\n";
                logger_->log(logging_data += "not found | invalid user record: no comma after rating\n");
                return lambda_(server_error("invalid user record"));
            }
            user_info.rating = atoi(record.substr(rating + 10, comma).c_str());
            if (user_info.rating == 0) {
                std::cout << "\t\tnot found | cannot convert rating\n";
                logger_->log(logging_data += "not found | cannot convert rating\n");
                return lambda_(server_error("invalid user record"));
            }
            
            // avatar url
            auto avatar = record.find("\"avatar\": \"");
            if (avatar == std::string::npos) {
                std::cout << "\t\tnot found | invalid user record: no avatar\n";
                logger_->log(logging_data += "not found | invalid user record: no avatar\n");
                return lambda_(server_error("invalid user record"));
            }
            comma = record.substr(avatar + 11).find('\"');
            //if (comma == std::string::npos)
            //    comma = record.substr(avatar + 11).find('\n');
            //if (comma == std::string::npos)
            //    comma = record.substr(avatar + 11).find('}');
            if (comma == std::string::npos) {
                std::cout << "\t\tnot found | invalid user record: no object ending\n";
                logger_->log(logging_data += "not found | invalid user record: no object ending\n");
                return lambda_(server_error("invalid user record"));
            }
            user_info.avatar = record.substr(avatar + 11, comma);

            std::cout << "REGISTER parsing results:\n" << "\t\t| uid: | " << user_info.id << "\n";
            std::cout << "\t\t| name: | " << user_info.nickname << "\n";
            std::cout << "\t\t| rating: | " << user_info.rating << "\n";
            std::cout << "\t\t| avatar: | " << user_info.avatar << "\n";
            
            user = std::make_shared<User>(user_info);
            std::cout << "user N " << serializeTimePoint(user->get_token(), "%y-%m-%d-%H_%M_%S") << ' ';

            const auto [active_user, success] = active_users_->insert({ user->get_token_string(), user });
            if (success)
                std::cout << " added to the User Map successfully" << std::endl;
            else
                std::cout << " has not been added to the map | FAIL" << std::endl;

            // sends the cookie
            return start_cookie_timer(user->get_token(), COOKIE_LIFETIME, req.version(), req.keep_alive(), logging_data);
        }

        auto start_game_target = target.find("/start_game/");
        if (start_game_target != std::string::npos) {
            std::cout << "parse url: start_game: from cookie: ";
            auto cookie = target.substr(start_game_target + 12);
            std::cout << cookie << '\n';

            auto active_user = active_users_->find(cookie);
            if (active_user != active_users_->end()) {
                std::cout << "Found user № " << active_user->first << " in the User Map" << '\n';
                user = active_user->second;
                return on_queue(std::move(logging_data), logger_, req.version());
            }
            else {
                std::cout << "Not found user № " << cookie << " in the User Map" << '\n';
                return lambda_(not_found("no such token or token expired"));
            }
        }

        // Build the path to the requested file
        std::string path = path_cat(*doc_root_, target);
        if (req.target().back() == '/')
            path.append("index.html");

        // getting file
        beast::error_code ec;
        http::file_body::value_type body;
        http::string_body::value_type string_body;

        logging_data += req.method_string().to_string() + "-req file: " + req.target().to_string() + "\n";

        if (req.method() == http::verb::post) {
            // go to DB write data
        }
        else {
            // Attempt to open the file
            std::ifstream in(path);
            
            // Handle the case where the file doesn't exist
            if (!in.is_open()) {
                logger_->log(logging_data += "fail: unreachable target: " + target);
                return lambda_(not_found(req.target()));
            }

            size_t bytes_read = 1;
            std::string content;
            char* block = new char[1024];
            while (bytes_read) {
                bytes_read = static_cast<size_t>(in.readsome(block, 1024));
                std::string block_string(block, bytes_read);
                content += block_string;
            }
            delete[] block;

            // Respond to HEAD request
            if (req.method() == http::verb::head)
            {
                http::response<http::string_body> res{ http::status::ok, req.version() };
                res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
                res.set(http::field::content_type, mime_type(path));
                res.content_length(content.size());
                res.keep_alive(req.keep_alive());
                logger_->log(logging_data += "OK");
                return lambda_(std::move(res));
            }

            http::response<http::string_body> res{
                std::piecewise_construct,
                std::make_tuple(content),
                std::make_tuple(http::status::ok, req.version())
            };

            res.set(http::field::server, BOOST_BEAST_VERSION_STRING);
            res.set(http::field::content_type, mime_type(path));
            res.content_length(content.size());
            res.keep_alive(req.keep_alive());
            logger_->log(logging_data += "OK\nCreating a response of " + std::to_string(content.size()) + " bytes\n");
            return lambda_(std::move(res));
        }
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
    beast::flat_buffer buffer_;
    std::string buffer_str_;
    std::shared_ptr<std::string const> doc_root_;
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
    {
    }
    // Get on the correct executor
    void run()
    {
        if (BASIC_DEBUG_WS) std::cout << "WS: " << this << " run\n";
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
        if (BASIC_DEBUG_WS) std::cout << "WS: " << this << " on run\n";

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
        if (BASIC_DEBUG_WS) std::cout << "WS: " << this << " on accept\n";
        if (ec)
            return fail(ec, "accept");

        // Read a message
        do_read();
    }

    void  do_read()
    {
        if (BASIC_DEBUG_WS) std::cout << "WS: " << this << " do read\n";
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
        if (BASIC_DEBUG_WS) std::cout << "WS: " << this << " on read\n";
        boost::ignore_unused(bytes_transferred);

        // This indicates that the session was closed
        if (ec == websocket::error::closed) {
            if (BASIC_DEBUG_WS) std::cout << "WS: " << this << " client closed connection\n";
            return;
        }

        if (ec)
            fail(ec, "read");

        handle_request();
        
    }


    // TODO ERRORS!
    void handle_request() {
        auto res = std::make_shared<std::string>();
        auto req = beast::buffers_to_string(buffer_.data());
        if (BASIC_DEBUG_WS) std::cout << "Got an request! : " << req << "\n";

        if (req == "NEED CLOSE") {
            (*res) = "OK | CLOSE";
            return write(res);
        }

        // parse code
        auto code_pos = req.find("\"code\": \"");
        if (code_pos == std::string::npos) {
            std::cout << "\tno \"code\"\n";
            (*res) = "What is your code?";
            return write(res);
        }
        code_pos += 9;
        size_t delim = req.substr(code_pos).find('\"');
        if (delim == std::string::npos) {
            std::cout << "\tno \"code\" ending\n";
            (*res) = "no \"code\" ending";
            return write(res);
        }
        auto code = req.substr(code_pos, delim);
        std::cout << "\t|code|: " << code << std::endl;


        // WS request to say they are ready to start the game
        // WS reconnecting may be done with sending "start" once more
        if (code == "start") {
            std::cout <<"Parsing start\n";
            auto game_token = req.find("\"game_token\": \"");
            if (game_token == std::string::npos) {
                std::cout << "\tNo Game_token\n";
                (*res) = "\tNo game token";
                return write(res);
            }
            auto comma = req.substr(game_token + 15).find('\"');
            if (comma == std::string::npos) {
                std::cout << "\tNo comma after game_token\n";
                (*res) = "No comma after game token";
                return write(res);
            }
            // token
            auto token = req.substr(game_token + 15, comma);
            if (MOVE_PARSE_DEBUG) std::cout << "\t|game_token:| " << token << "\n";
            auto uid = req.find("\"uid\": ");
            if (uid == std::string::npos) {
                std::cout << "\tNo uid\n";
                (*res) = "\tNo uid";
                return write(res);
            }
            auto closing_bracket = req.substr(uid + 7).find('}');
            if (closing_bracket == std::string::npos) {
                std::cout << "\tNo closing_bracket\n";
                (*res) = "No closing bracket after uid";
                return write(res);
            }
            // uid
            int id = atoi((req.substr(uid + 7, closing_bracket)+ "\0").c_str());
            if (MOVE_PARSE_DEBUG) std::cout << "\t|uid|: " << id << std::endl;

            // game
            auto games = MQSingleton::instance().get().get_games();
            auto game_pair = games->find(token);
            if (game_pair == games->end()) {
                std::cout << "\tGame with token " << token << " is not found\n";
                (*res) = "Game not found";
                return write(res);
            }

            // session filling
            auto game = game_pair->second;
            // it is a message from a white player
            if (id == game->wPlayer->get_user()->get_id()) {
                game->wPlayer->set_session(shared_from_this());
                //game->wPlayer->all_available_Moves();
            }
            if (id == game->bPlayer->get_user()->get_id()) {
                game->bPlayer->set_session(shared_from_this());
                //game->prepare_turn();
                //game->bPlayer->all_available_Moves();
            }
            if (id != game->bPlayer->get_user()->get_id() && id != game->wPlayer->get_user()->get_id()) {
                std::cout << "\tPlayer with uid " << id << " does not belong this game! (game token: " << game->get_token_string() << ").\n";
                std::cout << "\t\tWhite player has uid: " << game->wPlayer->get_user()->get_id() << "\n";
                std::cout << "\t\tBlack player has uid: " << game->bPlayer->get_user()->get_id() << "\n";
                (*res) = "Player with uid " + id + std::string(" does not belong this game! (game token : ") + game->get_token_string() + ")";
                return write(res);
            }

            // game start
            if (game->bPlayer->get_session() != nullptr && game->wPlayer->get_session() != nullptr) {
                game->prepare_turn();

                // message to white player
                auto info = game->send_info();
                auto avail = game->wPlayer->access();
                std::stringstream ss;
                ss << "[\n";
                for (std::array<size_t, M> out : avail)
                    ss << "\t\t[" << out[0] * 8 + out[1] << ", " << out[2] * 8 + out[3] << "],\n";
                ss << "\t]";
                std::string msg_to_white = (boost::format(MOVE_RESPONSE)
                    % ss.str()
                    % info.isPlayer
                    % info.isGame
                    % int(info.isVictory)
                    % info.isCheck
                    % (info.turn[0] * 8 + info.turn[1])
                    % (info.turn[2] * 8 + info.turn[3])
                    ).str();
                (*res) = msg_to_white;
                return write_game_start(game, res, id);
            }
            else {
                (*res) = "wait for opponent connection";
                //return write_short(res);
                return write(res);
            }
        }        
        
        // TODO: over
        if (code == "move") {

            // parse move
            game_error_code ec;
            Move m = get_move(req, ec);
            if (ec) {
                print_game_error_code(ec);
                (*res) = game_error_code_to_string(ec);
                return write(res);
            }

            // get game
            auto games = MQSingleton::instance().get().get_games();
            auto gameandtoken = games->find(m.game_token);
            if (gameandtoken == games->end()) {
                (*res) = "Invalid game token";
                return write(res);
            }

            auto game = gameandtoken->second;
            GInfo info = game->send_info();

            std::array<size_t, M> turn;
            turn[0] = m.prev / 8;
            turn[1] = m.prev % 8;
            turn[2] = m.cur / 8;
            turn[3] = m.cur % 8;
            int validation = game->run_turn(turn);

            if (!validation)
                std::cout << "\tMove is valid\n";
            else {
                std::cout << "\tMove is invalid\n";
                (*res) = "Move is invalid";
                return write(res);
            }

            game->prepare_turn();
            std::vector<std::array<size_t, M>>& avail = game->wPlayer->access();
            if (m.id == game->wPlayer->get_user()->get_id()) {
                avail = game->bPlayer->access();
            }


            info = game->send_info();
            std::cout << "\tprepare2";
            std::cout << avail.size();
            std::stringstream ss;
            ss << "[\n";
            for (std::array<size_t, M> out : avail)
                ss << "\t\t[" << out[0] * 8 + out[1] << ", " << out[2] * 8 + out[3] << "],\n";
            ss << "\t]";
            std::string content = (boost::format(MOVE_RESPONSE)
                               % ss.str()
                               % info.isPlayer
                               % info.isGame
                               % (int)info.isVictory
                               % info.isCheck
                               % (info.turn[0] * 8 + info.turn[1])
                               % (info.turn[2] * 8 + info.turn[3])
                               ).str();
            (*res) = content;

            auto enemy_session = game->enemy(m.id)->get_session();

            if (enemy_session != nullptr) {
                if (enemy_session != shared_from_this())
                    enemy_session->write_short(res);
                else
                    std::cout << "\tError: enemy_session is nullptr\n";
               
            }
            if (!info.isGame) {//game over
                write(res);
            }

            buffer_.consume(buffer_.size());
            do_read();
        }
    }


    void write(std::shared_ptr<std::string> res) {
        if (BASIC_DEBUG_WS) std::cout << "WS: " << this << " write\n";
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
        if (BASIC_DEBUG_WS) std::cout << "WS: " << this << " on write\n";

        boost::ignore_unused(bytes_transferred);

        if (ec)
            return fail(ec, "write");

        // Clear the buffer
        buffer_.consume(buffer_.size());

        // Do another read
        do_read();
    }

    // simple write with no this session event-loop continuation
    void write_short(std::shared_ptr<std::string> res) {
        if (BASIC_DEBUG_WS) std::cout << "WS: " << this << " write short\n";
        stream_.text(stream_.got_text());
        stream_.async_write(
            asio::buffer(*res),
            [s = shared_from_this(), res](beast::error_code ec, size_t bytes_transferred) mutable {
            if (BASIC_DEBUG_WS) std::cout << "WS: " << s << "on write short\n";
            boost::ignore_unused(bytes_transferred);
            if (ec)
                return fail(ec, "write");
            // Clear the buffer
            s->buffer_.consume(s->buffer_.size());
        });
    }


    void write_game_start(std::shared_ptr<GameSession> game, std::shared_ptr<std::string> msg_to_white, uid id_last) {
        auto white = game->wPlayer->get_session();
        auto black = game->bPlayer->get_session();
        if (BASIC_DEBUG_WS) std::cout << "WS: " << this << " write game start\n";
        
        
        if (id_last == game->wPlayer->get_user()->get_id())
            white->write(msg_to_white);
        else
            white->write_short(msg_to_white);

        if (id_last == game->bPlayer->get_user()->get_id())
            return black->write(std::make_shared<std::string>("started"));
        else
            return black->write_short(std::make_shared<std::string>("started"));
    }

    Move get_move(std::string& req, game_error_code& ec) {
        if (MOVE_PARSE_DEBUG) std::cout << "parsing move\n";
        Move m{};

        // game_token: %s,
        auto game_token = req.find("\"game_token\": \"");
        if (game_token == std::string::npos) {
            ec = game_error_code::no_game_token;
            return m;
        }
        auto comma = req.substr(game_token + 15).find('\"');
        if (comma == std::string::npos) {
            ec = invalid_format;
            return m;
        }
        m.game_token = req.substr(game_token + 15, comma);
        if (MOVE_PARSE_DEBUG) std::cout << "\t\t/game_token:/ " << m.game_token << "\n";

        // uid: %zu,
        auto uid = req.find("\"uid\": ");
        if (uid == std::string::npos) {
            ec = game_error_code::invalid_uid;
            return m;
        }
        comma = req.substr(uid + 6).find(',');
        if (comma == std::string::npos) {
            ec = invalid_format;
            return m;
        }

        // TODO: check that 
        m.id = atoi(req.substr(uid + 6, comma).c_str());
        if (MOVE_PARSE_DEBUG) std::cout << "\t\t/uid:/ " << m.id << "\n";

        // prev: %zu
        auto prev = req.find("\"prev\": ");
        if (prev == std::string::npos) {
            ec = game_error_code::no_prev_move;
            return m;
        }
        
        comma = req.substr(prev + 8).find(',');
        if (comma == std::string::npos) {
            ec = invalid_format;
            return m;
        }

        // TODO: check that 
        m.prev = atoi(req.substr(prev + 8, comma).c_str());
        if (MOVE_PARSE_DEBUG) std::cout << "\t\t/prev:/ " << m.prev << "\n";

        // cur: %zu,
        auto cur = req.find("\"cur\": ");
        if (cur == std::string::npos) {
            ec = game_error_code::no_cur_move;
            return m;
        }
        comma = req.substr(cur + 7).find(',');
        if (comma == std::string::npos)
            comma = req.substr(cur + 7).find('\n');
        if (comma == std::string::npos)
            comma = req.substr(cur + 7).find('}');
        if (comma == std::string::npos) {
            ec = invalid_format;
            return m;
        }
        
        // TODO: check that 
        m.cur = atoi(req.substr(cur + 7, comma).c_str());
        if (MOVE_PARSE_DEBUG) std::cout << "\t\t/cur:/ " << m.cur << "\n";
        ec = game_error_code::ok;
        return m;
    }
};
#endif //CHECKMATES_NET_H

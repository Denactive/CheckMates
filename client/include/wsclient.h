#ifndef WSCLIENT_H
#define WSCLIENT_H

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#define WBASIC_DEBUG 1

#define BOOST_DATE_TIME_NO_LIB
#include <boost/beast/core.hpp>
#include <boost/beast/core/buffers_to_string.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>
#include <thread>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <QDebug>

namespace asio = boost::asio;
namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

void wsfail(beast::error_code ec, char const* what);
/*
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
    asio::io_context ioc_;
};
*/

class wssession : public std::enable_shared_from_this<wssession>
{
    tcp::resolver resolver_;
    websocket::stream<beast::tcp_stream> ws_;
    beast::flat_buffer buffer_;
    std::string host_;
    std::string text_;
    bool need_close = false;
    std::string close_str = "NEED_CLOSE";


public:
    explicit wssession(net::io_context& ioc)
        : resolver_(net::make_strand(ioc))
        , ws_(net::make_strand(ioc)){}

    void run(char const* host, char const* port);
    void onResolve(beast::error_code ec, tcp::resolver::results_type results);
    void onConnect(beast::error_code ec, tcp::resolver::results_type::endpoint_type);
    void onHandshake(beast::error_code ec);

    void onRead(beast::error_code ec, std::size_t bytes_transferred);
    void doRead();

    void close();
    void doClose();
    void onClose(beast::error_code ec);

    void write(std::string& msg);
    void onWrite(beast::error_code ec, std::size_t bytes_transferred, std::string& msg);

    void doSomeWork(beast::error_code ec, std::size_t bytes_transferred);
    void send() {};

    std::string buffer() { return beast::buffers_to_string(buffer_.data()); }

    ~wssession() {qDebug()<<"fuck i die\n";};
};

class SessionSingleton
{
public:
    static SessionSingleton& instance()
    {
        static SessionSingleton singleton;
        return singleton;
    }

    std::shared_ptr<wssession>& get() { return ws; }
    asio::io_context& get_ioc() { return ioc_; }

    // Other non-static member functions
private:
    SessionSingleton()
        : ws(std::make_shared<wssession>(ioc_)) {}             // Private constructor
    ~SessionSingleton() {}
    SessionSingleton(const SessionSingleton&);                 // Prevent copy-construction
    SessionSingleton& operator=(const SessionSingleton&);      // Prevent assignment
    std::shared_ptr<wssession> ws;
    asio::io_context ioc_;
};


void runGame();

#endif // WSCLIENT_H

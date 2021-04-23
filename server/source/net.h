//
// Created by denactive on 14.04.2021.
//

#ifndef CHECKMATES_NET_H
#define CHECKMATES_NET_H

#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <boost/date_time.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
//#include <boost/regex.hpp>
//#include <boost/beast/core.hpp>
//#include <boost/shared_ptr.hpp>
//#include <boost/utility/result_of.hpp>
//#include <boost/beast/ssl.hpp>
//#include <boost/beast/websocket.hpp>
//#include <boost/beast/websocket/ssl.hpp>
//#include <boost/asio/strand.hpp>
//#include <boost/asio/ip/tcp.hpp>
//#include <boost/asio/dispatch.hpp>

#define ASIO_STANDALONE
#include <boost/asio.hpp>
#include <boost/asio/buffer.hpp>
#include <boost/asio/ts/internet.hpp>

#include <string>
#include <vector>

typedef struct {
    std::string ip;
    // sock
} Connection;

class HTTP_document {
public:
    HTTP_document (std::vector<std::string> headers, std::string message):
        headers_(headers), message_(message) {
    }
    std::string get_message();
    std::vector<std::string> get_headers() { return headers_;};
    void set_message(std::string msg) {message_ = msg;}
    void add_header(std::string hdr) {headers_.push_back(hdr);}
    short get_code() {return code_;}

private:
    std::vector<std::string> headers_;
    std::string message_;
    short code_ = 0;
};

class ISerializer {
public:
    virtual std::string serialize(std::string) = 0;
    virtual std::string deserialize(std::string) = 0;
};

class JSON_serializer: ISerializer {
public:
    std::string serialize(std::string) override;
    std::string deserialize(std::string) override;
};

class WS_format {
public:
    WS_format(ISerializer& s): serializer(s) {}
    WS_format() = delete;

    void run();
    void game_request_handler();
    void game_response_handler();
    void chat_handler();
private:
    ISerializer& serializer;
};

class HTTP_format {
public:
    HTTP_format(ISerializer& s): serializer(s) {}
    HTTP_format() = delete;

    void run();
    void request_handler();
    void authorize_handler();
    void register_handler();
private:
    ISerializer& serializer;
};

class Net {
public:
    Connection accept();
    std::string read();
    void write(std::string);

private:
    //void on_read(boost::system::error_code err, size_t bytes);
    //void on_write(boost::system::error_code err, size_t bytes);
    static const int max_msg = 1024;
    char read_buffer_ [max_msg];
    char write_buffer_ [max_msg];

};

class ILogger {
    virtual void log(std::string data) = 0;
};

class ConsoleLogger: ILogger {
    void log(std::string data) override;
};
#endif //CHECKMATES_NET_H
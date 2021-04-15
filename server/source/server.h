//
// Created by denactive on 14.04.2021.
//

#ifndef CHECKMATES_SERVER_H
#define CHECKMATES_SERVER_H

#include "net.h"
#include <string>

class Options {
public:
    Options(std::string owner, std::string ip, unsigned short port):
        owner_(owner), ip_(ip), port_(port) {
    }
    std::string get_info() { return "owner: " + owner_ + "\nip: " + ip_ + ":" + std::to_string(port_); }

    void set_port(unsigned short port) { port_ = port; }
    void set_ip(std::string ip) { ip_ = ip; }
    void set_owner(std::string owner) { owner_ = owner; }

    unsigned short get_port() { return port_; }
    std::string get_ip() { return ip_; }
    std::string get_owner() { return owner_; }

private:
    std::string owner_;
    std::string ip_;
    unsigned short port_;
};

class Server {
public:
    Server(Options opts):
            opts_(opts) {
    }
    void run();
    void stop();
    void restart();
    bool is_running();

private:
    Options opts_;
    bool started_ = 0;
    boost::asio::io_service service_;
    Net net_;
};


#endif //CHECKMATES_SERVER_H

//
// Created by denactive on 14.04.2021.
//

#ifndef CHECKMATES_SERVER_H
#define CHECKMATES_SERVER_H

#include "net.h"
#include "matcher.h"
// matcher contains GameSession (starts games)
// GameSession contains Player, which contains User
// User contains Community
// Community is independent
#include <string>
#include <iostream>

class Options {
public:
    Options(std::string owner, std::string ip, unsigned short port):
        owner_(owner), ip_(ip), port_(port) {
    }
    std::string get_info() { return "owner: " + owner_ + " | ip: " + ip_ + ":" + std::to_string(port_); }

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
    Server(Options opts) :
        opts_(opts) {
        net_ = Net();
    }

    void run();
    void stop();
    void restart();

    bool is_running() { return started_; }

private:
    Options opts_;
    Net net_;
    MatcherQueue mq_;
    bool started_ = false;
    boost::asio::io_service service_;
};

#endif //CHECKMATES_SERVER_H
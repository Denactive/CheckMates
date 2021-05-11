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


// =======================[ Options ]=========================


class Options {
public:
    Options(
        std::string owner,
        std::string ip_host,
        unsigned short port,
        std::string doc_root)
        : owner_(owner)
        , ip_(asio::ip::make_address(ip_host))
        , port_(port)
        , doc_root_(std::make_shared<std::string>(doc_root))
    {
    }

    std::string get_info() { return "owner: "; }// + owner_ + " | ip: " + ip_ + ":" + std::to_string(port_) + " | doc dir:" + doc_root_; }

    //const unsigned short&   get_port() { return port_; }
    //const std::string&      get_ip() { return ip_; }
    //const std::string&      get_owner() { return owner_; }
    //std::shared_ptr<std::string const> const& get_doc_root() { return doc_root_; }

//private:
    const std::string owner_;
    // const std::string ip_;
    const unsigned short port_;
    //const std::string doc_root_;
    asio::ip::address const ip_;
    //auto const port = static_cast<unsigned short>(std::atoi(argv[2]));
    std::shared_ptr<std::string> const doc_root_;
    //auto const threads = std::max<int>(1, std::atoi(argv[4]));
};


// =======================[ Server ]=========================


class Server {
public:
    Server(Options opts)
        : opts_(opts)
    {
    }

    int run(asio::io_context& ioc);
    int stop();
    int restart();

    bool is_running() { return started_; }

private:

    Options opts_;
    MatcherQueue mq_;
    bool started_ = false;
    unsigned short const threads_num_ = 1;
};


// =======================[ Listener ]=========================


// Accepts incoming connections and launches the sessions
class Listener : public std::enable_shared_from_this<Listener>
{
    asio::io_context& ioc_;
    tcp::acceptor acceptor_;
    std::shared_ptr<std::string const> doc_root_;

public:
    Listener(
        asio::io_context& ioc,
        tcp::endpoint endpoint,
        std::shared_ptr<std::string const> const& doc_root)
        : ioc_(ioc)
        , acceptor_(asio::make_strand(ioc))
        , doc_root_(doc_root)
    {
        beast::error_code ec;

        // Open the acceptor
        acceptor_.open(endpoint.protocol(), ec);
        if (ec)
        {
            fail(ec, "open");
            return;
        }

        // Allow address reuse
        acceptor_.set_option(asio::socket_base::reuse_address(true), ec);
        if (ec)
        {
            fail(ec, "set_option");
            return;
        }

        // Bind to the server address
        acceptor_.bind(endpoint, ec);
        if (ec)
        {
            fail(ec, "bind");
            return;
        }

        // Start listening for connections
        acceptor_.listen(
            asio::socket_base::max_listen_connections, ec);
        if (ec)
        {
            fail(ec, "listen");
            return;
        }
    }

    // Start accepting incoming connections
    void
        run()
    {
        do_accept();
    }

private:
    void
        do_accept()
    {
        // The new connection gets its own strand
        acceptor_.async_accept(
            asio::make_strand(ioc_),
            beast::bind_front_handler(
                &Listener::on_accept,
                shared_from_this()));
    }

    void
        on_accept(beast::error_code ec, tcp::socket socket)
    {
        if (ec)
        {
            fail(ec, "accept");
        }
        else
        {
            // Create the session and run it
            std::make_shared<Session>(
                std::move(socket),
                doc_root_)->run();
        }

        // Accept another connection
        do_accept();
    }
};

#endif //CHECKMATES_SERVER_H
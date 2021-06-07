//
// Created by denactive on 14.04.2021.
//

#ifndef CHECKMATES_SERVER_H
#define CHECKMATES_SERVER_H

#include "net.h"
//#include "matcher.h"
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
        const  std::string& type,
        std::string owner,
        std::string ip_host,
        unsigned short port,
        const std::string& doc_root,
        const  std::string& log_dir)
        : type_(std::make_shared<std::string>(type))
        , owner_(owner)
        , ip_(asio::ip::make_address(ip_host))
        , port_(port)
        , doc_root_(std::make_shared<std::string>(doc_root))
        , log_dir_(std::make_shared<std::string>(log_dir))
        , db_(std::make_shared<DBServer>(doc_root))
    {
    }

    std::string get_info() { return "owner: " + owner_ + " | ip: " + ip_.to_string() + ":" + std::to_string(port_) + " (" + *type_ + ")\ndoc dir: " + *doc_root_ + "\nlog dir: " + *log_dir_ + '\n'; }

    std::shared_ptr<std::string> type_;
    const std::string owner_;
    const unsigned short port_;
    asio::ip::address const ip_;
    std::shared_ptr<std::string> const doc_root_;
    std::shared_ptr<std::string> const log_dir_;
    const std::shared_ptr<IDBServer> db_;
};


// =======================[ Server ]=========================


class Server {
public:
    Server(Options& opts,
        std::shared_ptr<UserMap>& active_users
    )
        : opts_(opts)
        , active_users_(active_users)
    {
    }

    int run(asio::io_context& ioc);
    int stop();
    int restart();

    bool is_running() { return started_; }

private:

    Options opts_;
    bool started_ = false;
    std::shared_ptr<UserMap>& active_users_;
};


// =======================[ Listener ]=========================


// Accepts incoming connections and launches the sessions
class Listener : public std::enable_shared_from_this<Listener>
{
    asio::io_context& ioc_;
    tcp::acceptor acceptor_;
    std::shared_ptr<std::string const> doc_root_;
    std::shared_ptr<std::string const> log_dir_;
    std::shared_ptr<std::string const> type_;
    const std::shared_ptr<IDBServer> db_;
    std::shared_ptr<UserMap>& active_users_;

public:
    Listener(
        asio::io_context& ioc,
        tcp::endpoint endpoint,
        std::shared_ptr<std::string const> const& type,
        std::shared_ptr<std::string const> const& doc_root,
        std::shared_ptr<std::string const> const& log_dir,
        const std::shared_ptr<IDBServer>& db,
        std::shared_ptr<UserMap>& active_users
    )
        : ioc_(ioc)
        , acceptor_(asio::make_strand(ioc))
        , type_(type)
        , doc_root_(doc_root)
        , log_dir_(log_dir)
        , db_(db)
        , active_users_(active_users)
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
            if (*type_ == "http")
                std::make_shared<Session>(
                    std::move(socket),
                    doc_root_,
                    log_dir_,
                    db_,
                    active_users_
                    )->run();
            if (*type_ == "ws")
                std::make_shared<WebSocketSession>(
                    std::move(socket),
                    doc_root_,
                    log_dir_,
                    db_
                    )->run();
        }

        // Accept another connection
        do_accept();
    }
};

#endif //CHECKMATES_SERVER_H
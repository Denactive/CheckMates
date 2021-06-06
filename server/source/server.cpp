//
// Created by denactive on 14.04.2021.
//
#include "server.h"

// TODO: read add timers


// =======================[ Server ]=========================


int Server::run(asio::io_context& ioc) {
    std::cout << "Server starts running\n" << opts_.get_info();
    started_ = true;

    // Create and launch a listening port
    std::make_shared<Listener>(ioc,
        tcp::endpoint{ opts_.ip_, opts_.port_ },
        opts_.type_,
        opts_.doc_root_,
        opts_.log_dir_,
        opts_.db_,
        active_users_
        )->run();

    return EXIT_SUCCESS;
}

int Server::stop() {
    std::cout << "Server has been stopped\n";
    started_ = false;
    return EXIT_SUCCESS;
}

int Server::restart() {
    std::cout << "Server restarts\n";
    stop();
    //run();
    return EXIT_SUCCESS;
}
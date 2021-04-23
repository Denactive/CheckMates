//
// Created by denactive on 14.04.2021.
//
#include "net.h"
#include "server.h"

// TODO: read about namespaces
// TODO: add timers

void Server::run() {
    std::cout << "Server starts running\n" << opts_.get_info();
    started_ = true;
    net_.accept();
}

void Server::stop() {
    std::cout << "Server has been stopped\n";
    started_ = false;
}

void Server::restart() {
    std::cout << "Server restarts\n";
    stop();
    run();
}

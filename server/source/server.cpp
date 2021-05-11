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
        opts_.doc_root_
        )->run();
    
    // Run the I/O service on the requested number of threads
    std::vector<std::thread> v;
    v.reserve(threads_num_ - 1);
    for (auto i = threads_num_ - 1; i > 0; --i)
        v.emplace_back(
            [&ioc]
            {
                ioc.run();
            });
    ioc.run();

    return EXIT_SUCCESS;
}

int Server::stop() {
    std::cout << "Server has been stopped\n";
    started_ = false;
    return 0;
}

int Server::restart() {
    std::cout << "Server restarts\n";
    stop();
    //run();
    return 0;
}
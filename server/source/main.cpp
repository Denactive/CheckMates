//
// Created by denactive on 14.04.2021.
//
#include "server.h"

// TODO: ������� request_hander_http ��� http � request_hander_ws ��� ws

int main() {
    // BE CAREFUL WITH FILEPATH
    Options opts("SaberLion-Devs", "25.40.253.246", 8000, 8001, "C:/Users/Denactive/source/repos/SaberDevs_CheckMates/server/storage");
    Server s(opts);

    const unsigned short threads_num = 1;
    asio::io_context ioc{ threads_num };

    s.run(ioc);
}
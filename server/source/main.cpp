//
// Created by denactive on 14.04.2021.
//
#include "server.h"

int main() {
    Options opts("SaberLion-Devs", "127.0.0.1", 8000);
    Server s(opts);
    s.run();
}
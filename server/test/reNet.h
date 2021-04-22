//
// Created by denactive on 22.04.2021.
//
// for testing Server
// мок не нужен. Подмени сеть удобным классом

#ifndef CHECKMATES_RENET_H
#define CHECKMATES_RENET_H

class NetFooley {
    Connection accept() {
        Connection res = {"000.000.000.000"};
        return res;
    }
    std::string read() {return "TestString"};
    void write(std::string);
};

#endif //CHECKMATES_RENET_H

//
// Created by denactive on 14.04.2021.
//

#ifndef CHECKMATES_SERVER_H
#define CHECKMATES_SERVER_H



#include <string>

class Options {
public:


private:
    std::string owner_;
    std::string ip_;
    unsigned short port_;
};

class Server {
public:
    void run();
    void stop();
    void restart();
    bool is_running();

private:
    bool started = 0;

};
#endif //CHECKMATES_SERVER_H

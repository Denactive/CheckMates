//
// Created by yura11011 on 15.04.2021.
//

#ifndef CHECKMATES_STUB_H
#define CHECKMATES_STUB_H
#include "GameSession.h"

class iMatcherQueue {
virtual int a() = 0;
};

class MatcherQueue: public iMatcherQueue {
    int a();
};


class Community {
    int a();
};

class Chat {
    int a();
};

class Connection {
    int a();
    int b;
};

#endif //CHECKMATES_STUB_H
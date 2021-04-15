//
// Created by denactive on 15.04.2021.
//

#ifndef CHECKMATES_MATCHER_H
#define CHECKMATES_MATCHER_H

//#include "user.h"
class IUser;

// todo: посмотреть про аррей
//#include <array>
#include <vector>
#include <queue>
// Todo: #include <singleton>
// Todo: #include <GameSession>

// затычка
class GameSession {
    bool t = 1;
};

class IMatcherQueue {
public:
    virtual GameSession& start_game() = 0;
    virtual void push_user(IUser& u) = 0;
};

class MatcherQueue: IMatcherQueue {
public:
    GameSession& start_game() override;
    void push_user(IUser& u) override;

private:
    // todo: learn more about std::queue
    std::vector< std::queue<const IUser*> > q_;
};


#endif //CHECKMATES_MATCHER_H

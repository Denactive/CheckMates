#pragma once
#include "GameSession.h"
//#include "User.h"
class IUser;

// todo: посмотреть про аррей
//#include <array>
#include <vector>
#include <queue>
// Todo: #include <singleton>
// Todo: #include <GameSession>



class IMatcherQueue {
public:
    virtual GameSession& start_game() = 0;
    virtual void push_user(IUser* u) = 0;
    virtual void pop_user(IUser* u) = 0;
};

class MatcherQueue: IMatcherQueue {
public:
    GameSession& start_game() override;
    void push_user(IUser* u) override;
    void pop_user(IUser* u) override;

private:
    // todo: learn more about std::queue
    std::vector< std::queue<const IUser*> > q_;
};




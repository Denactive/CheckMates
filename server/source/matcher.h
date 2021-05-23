#pragma  once

#include <iostream>
#include <queue>
#include <memory>

#include "GameSession.h"

class IMatcherQueue {
public:
    virtual std::shared_ptr<GameSession> start_game(std::shared_ptr<IUser> p1, std::shared_ptr<IUser> p2) = 0;
    virtual void push_user(std::shared_ptr<IUser> u) = 0;
    virtual void pop_user(std::shared_ptr<IUser> u) = 0;
};

class MatcherQueue: public IMatcherQueue {
public:
    MatcherQueue(){
        // test
        //auto s = std::make_shared<Session>("test");
        //auto u = std::make_shared<User>(*s);
        //u->set_user_data(2, "Youra", 14);
        //q_.push(u);
    }

    std::shared_ptr<GameSession> start_game(std::shared_ptr<IUser> p1, std::shared_ptr<IUser> p2) override;
    void push_user(std::shared_ptr<IUser> u) override;
    void pop_user(std::shared_ptr<IUser> u) override;

private:
    // todo: learn more about std::queue
    //std::vector< std::queue<std::shared_ptr<IUser>> > q_;
    std::queue<std::shared_ptr<IUser>> q_;
};





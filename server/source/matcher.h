#pragma  once

#include <iostream>
#include <queue>
#include <set>

#include "GameSession.h"

class IMatcherQueue {
public:
    virtual std::shared_ptr<GameSession> start_game(std::shared_ptr<IUser> p1, std::shared_ptr<IUser> p2) = 0;
    virtual bool push_user(std::shared_ptr<IUser> u) = 0;
    virtual bool pop_user(std::shared_ptr<IUser> u) = 0;
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
    bool push_user(std::shared_ptr<IUser> u) override;
    bool pop_user(std::shared_ptr<IUser> u) override;

    size_t active_games_cnt = 0;

private:
    // todo: learn more about std::queue
    //std::vector< std::queue<std::shared_ptr<IUser>> > q_;
    std::queue<std::shared_ptr<IUser>> q_;
    std::set<std::shared_ptr<GameSession>, GameSessionComparator> games_;
};





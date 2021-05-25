#pragma  once

#include <iostream>
#include <queue>

#include "GameSession.h"

class IMatcherQueue {
public:
    virtual std::shared_ptr<GameSession> start_game(std::shared_ptr<IUser> p1, std::shared_ptr<IUser> p2) = 0;
    virtual std::shared_ptr<GameSession> push_user(std::shared_ptr<IUser> u) = 0;
    virtual bool pop_user(std::shared_ptr<IUser> u) = 0;
};

class MatcherQueue: public IMatcherQueue {
public:
    MatcherQueue():
    games_(std::make_shared<GameSessionMap>())
    {
    }

    std::shared_ptr<GameSession> start_game(std::shared_ptr<IUser> p1, std::shared_ptr<IUser> p2) override;
    std::shared_ptr<GameSession> push_user(std::shared_ptr<IUser> u) override;
    bool pop_user(std::shared_ptr<IUser> u) override;

private:
    std::queue<std::shared_ptr<IUser>> q_;
    std::shared_ptr<GameSessionMap> games_;
};
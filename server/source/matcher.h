#pragma  once
#include "GameSession.h"
#include "User.h"

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





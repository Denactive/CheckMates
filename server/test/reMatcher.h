//
// Created by denactive on 25.04.2021.
//

#ifndef SERVER_REMATCHER_H
#define SERVER_REMATCHER_H

class reMatcher: IMatcherQueue {
public:
    MOCK_METHOD(GameSession&, start_game, (), (override));
    MOCK_METHOD(void, push_user, (IUser* u), (override));
    MOCK_METHOD(void, pop_user, (IUser* u), (override));
};

#endif //SERVER_REMATCHER_H

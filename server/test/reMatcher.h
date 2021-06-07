//
// Created by denactive on 25.04.2021.
//

#ifndef SERVER_REMATCHER_H
#define SERVER_REMATCHER_H

class reMatcher: public IMatcherQueue {
public:
    MOCK_METHOD(std::shared_ptr<GameSessionMap> ,get_games, (), (override));
    MOCK_METHOD(std::shared_ptr<GameSession>, start_game, (std::shared_ptr<IUser>, std::shared_ptr<IUser>), (override));
    MOCK_METHOD(std::shared_ptr<GameSession>, push_user, (std::shared_ptr<IUser>), (override));
};

#endif //SERVER_REMATCHER_H

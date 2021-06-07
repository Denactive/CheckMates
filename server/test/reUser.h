//
// Created by denactive on 23.04.2021.
//

#ifndef SERVER_REUSER_H
#define SERVER_REUSER_H

#include <string>
#include "gmock/gmock.h"
#include "../source/User.h"

class reUser: public IUser {
public:
    MOCK_METHOD(UserInfo, get_info, (), (override));
    MOCK_METHOD(uid, get_id, (), (override));
    MOCK_METHOD(std::string, get_nickname, (), (override));
    MOCK_METHOD(int, get_rating, (), (override));
    MOCK_METHOD(void, set_rating, (int), (override));
    MOCK_METHOD(Stats, get_full_stats, (IDBServer&), (override));
    MOCK_METHOD(void, set_user_data, (uid, std::string, int));
    MOCK_METHOD(std::shared_ptr<ICommunity>, create_community, ());
    MOCK_METHOD(std::shared_ptr<IChat>, create_chat, (std::set<uid>));
    MOCK_METHOD(Cookie, get_token, ());
    MOCK_METHOD(std::string, get_token_string, ());
    MOCK_METHOD(std::string, get_avatar, ());
};

#endif //SERVER_REUSER_H

//
// Created by denactive on 23.04.2021.
//

#ifndef SERVER_REUSER_H
#define SERVER_REUSER_H

#include <string>
#include "gmock/gmock.h"
#include "../source/User.h"

class reUser: IUser {
public:
    MOCK_METHOD(UserInfo, get_info, (), (override));
    MOCK_METHOD(uid, get_id, (), (override));
    MOCK_METHOD(std::string, get_nickname, (), (override));
    MOCK_METHOD(int, get_rating, (), (override));
    MOCK_METHOD(void, set_rating, (int), (override));
    MOCK_METHOD(Stats, get_full_stats, (IDBServer&), (override));
    MOCK_METHOD(Community*, create_community ,(), (override));
    MOCK_METHOD(Chat*, create_chat, (std::set<uid>), (override));
};

#endif //SERVER_REUSER_H

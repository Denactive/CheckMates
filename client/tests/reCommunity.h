#ifndef RECOMMUNITY_H
#define RECOMMUNITY_H

#include "gmock/gmock.h"
#include "../include/community.h"

class MockUser : public IUser{
public:
    MOCK_CONST_METHOD0(getUserRating, int());
    MOCK_CONST_METHOD0(getUserPassword, std::string());
    MOCK_CONST_METHOD0(getLogin, std::string());
    MOCK_CONST_METHOD0(gameTime, int());
    MOCK_CONST_METHOD0(getUserStep, std::pair<int, int>());
    MOCK_CONST_METHOD1(changeRating, int(int newRating));
    MOCK_METHOD1(setPassword, void(std::string password));
    MOCK_METHOD1(setLogin, void(std::string login));
};

#endif // RECOMMUNITY_H

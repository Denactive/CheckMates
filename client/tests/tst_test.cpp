#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace testing;
using ::testing::Return;

#include "../include/community.h"
#include "../include/database.h"

class MockUser : public IUser{
public:
    MOCK_CONST_METHOD0(getUserRating, int());
    MOCK_CONST_METHOD0(getUserPassword, std::string());
    MOCK_CONST_METHOD0(getLogin, std::string());
    MOCK_CONST_METHOD0(gameTime, std::string());
    MOCK_CONST_METHOD0(getUserStep, std::pair<int, int>());
    MOCK_CONST_METHOD1(changeRating, int(int newRating));
    MOCK_METHOD1(setPassword, void(std::string password));
    MOCK_METHOD1(setLogin, void(std::string login));
};

using ::testing::AtLeast;
TEST(Rating, correctRating) {
    MockUser mock;
    EXPECT_CALL(mock,changeRating(int(1))).WillOnce(Return(1));
    EXPECT_EQ(mock.changeRating(1), 1);
    EXPECT_EQ(mock.getUserRating(), 1);
}

TEST(getUserStep, correctStep) {
    MockUser mock;
    EXPECT_CALL(mock,getUserStep()).WillOnce(Return(std::pair<int,int>(1,1)));
}

TEST(getUserPassword, correctPassword) {
    MockUser mock;
    mock.setPassword("1");
    EXPECT_CALL(mock, getUserPassword()).WillOnce(Return("1"));
}

TEST(getLogin, correctLogin) {
    MockUser mock;
    mock.setLogin("1");
    EXPECT_CALL(mock, getLogin()).WillOnce(Return("1"));
}

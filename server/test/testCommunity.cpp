//
// Created by svetlana on 25.04.2021.
//

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "matcher.h"
#include "GameSession.h"
#include "community.h"
#include "reCommunity.h"

#include <string>

using ::testing::Return;
using ::testing::AtLeast;

TEST(Chat, mock) {
    MockChat mock;
    std::string history = "hist";
    std::set<uid> list_members;
    Chat chat;

    ON_CALL(mock, get_history()).WillByDefault(Return(history));
    ON_CALL(mock, get_user_list()).WillByDefault(Return(list_members));

    EXPECT_EQ(chat.get_history(), "");
    EXPECT_EQ(chat.get_user_list(), list_members);
}

TEST(Community, mock) {
    MockCommunity mock;
    std::set<uid> users;
    std::set<uid> moderators;
    uid admin = 0;
    std::set<Rewards> rewards;
    Chat* chat = nullptr;
    Community community(users);

    ON_CALL(mock, get_user_list()).WillByDefault(Return(users));
    ON_CALL(mock, get_moderators_list()).WillByDefault(Return(moderators));
    ON_CALL(mock, get_admin()).WillByDefault(Return(admin));
    ON_CALL(mock, get_rewards()).WillByDefault(Return(rewards));
    ON_CALL(mock, get_group_chat()).WillByDefault(Return(chat));

    EXPECT_EQ(community.get_user_list(), users);
    EXPECT_EQ(community.get_moderators_list(), moderators);
    EXPECT_EQ(community.get_admin(), admin);
    EXPECT_EQ(community.get_rewards(), rewards);
    EXPECT_EQ(community.get_group_chat(), chat);
}

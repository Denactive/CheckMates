//
// Created by svetlana on 25.04.2021.
//

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "community.h"
#include "reCommunity.h"

#include <string>

using ::testing::Return;
using ::testing::AtLeast;

TEST(CommunityMock, Community) {
    // Arrange
    std::set<uid> list_members;
    list_members.insert(0);
    list_members.insert(1);
    list_members.insert(2);
    std::set<uid> res;

    reChat mock;
    ON_CALL(mock, get_user_list).WillByDefault(Return(res));

    // ACT
    Community c(list_members);
    res = c.get_group_chat()->get_user_list();

    // ASSERT
    EXPECT_EQ(res == list_members, true);
}

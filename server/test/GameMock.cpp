//
// Created by denactive on 25.04.2021.
//
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "matcher.h"
#include "reGameSession.h"

using ::testing::Return;
using ::testing::AtLeast;

TEST(NetMock, Matcher) {
    std::cout << "NetMock | Matcher " << std::endl;
    // Arrange
    MatcherQueue mq;
    reGameSession mg;

    EXPECT_CALL(mg, run).Times(AtLeast(1));

    // Act
    mq.start_game();

    // Assert
}
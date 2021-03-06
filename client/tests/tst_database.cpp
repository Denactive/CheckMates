#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace testing;
using ::testing::Return;

#include "../include/database.h"
#include "reDatabase.h"

using ::testing::AtLeast;
TEST(Stats, correctStats) {
    // arrange
    MockStats mock;
    Stats stats;
    Statistics st;
    stats.avgGameLen = 0;
    stats.gameLeavingPercentage = 0;
    stats.giveUpsPercentage = 0;
    stats.movesToWinQuantity = 0;
    stats.staleMatePercentage = 0;
    User * user = nullptr;

    ON_CALL(mock, getStats(user)).WillByDefault(Return(&stats));
    ON_CALL(mock, getAverageGameLen()).WillByDefault(Return(0));
    ON_CALL(mock, getAverageMovesToWinQuantity()).WillByDefault(Return(0));
    ON_CALL(mock, getStaleMatePercentage()).WillByDefault(Return(0));
    ON_CALL(mock, getGameLeavingPercentage()).WillByDefault(Return(0));
    ON_CALL(mock, giveUpsPercentage()).WillByDefault(Return(0));

    st.getAverageGameLen();
    st.getAverageMovesToWinQuantity();
    st.getStaleMatePercentage();
    st.getGameLeavingPercentage();
    st.giveUpsPercentage();

    EXPECT_EQ(st.getAverageGameLen(), -1);
    EXPECT_EQ(st.getAverageMovesToWinQuantity(), -1);
    EXPECT_EQ(st.getStaleMatePercentage(), -1);
    EXPECT_EQ(st.getGameLeavingPercentage(), -1);
    EXPECT_EQ(st.giveUpsPercentage(), -1);
}

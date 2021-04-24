#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace testing;
using ::testing::Return;

#include "../include/database.h"

class MockStats : public IStatistics{
public:
    MOCK_METHOD(Stats*, getStats, (User * user), (override));
    MOCK_METHOD((int), getAverageGameLen, (), (override));
    MOCK_METHOD((int), getAverageMovesToWinQuantity, (), (override));
    MOCK_METHOD((int), getStaleMatePercentage, (), (override));
    MOCK_METHOD((int), getGameLeavingPercentage, (), (override));
    MOCK_METHOD((int), giveUpsPercentage, (), (override));
};

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
    // assert
    // ... expect_eq
}

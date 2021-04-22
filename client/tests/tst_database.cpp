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
//TEST(Stats, correctStats) {
//    MockStats mock;
//    Stats stats;
//    stats.avgGameLen = 0;
//    stats.gameLeavingPercentage = 0;
//    stats.giveUpsPercentage = 0;
//    stats.movesToWinQuantity = 0;
//    stats.staleMatePercentage = 0;
//    User * user = nullptr;
//    EXPECT_CALL(mock, getStats(user)).WillOnce(Return(stats));
//}

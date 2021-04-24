#ifndef REDATABASE_H
#define REDATABASE_H

#include "gmock/gmock.h"
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

#endif // REDATABASE_H

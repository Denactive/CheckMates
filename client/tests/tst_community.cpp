#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace testing;
using ::testing::Return;

#include "../include/community.h"
#include "reCommunity.h"

using ::testing::AtLeast;
TEST(Rating, correctRating) {
    MockUser mock;
    EXPECT_CALL(mock,changeRating(int(1))).WillOnce(Return(1));
    EXPECT_EQ(mock.changeRating(1), 1);
}

#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "GameSession.h"


class reTurnControl {

public:
    MOCK_METHOD(time_t, GetTime, (const bool Turn) );
    MOCK_METHOD(bool, GetTurn, ());
};

using ::testing::Return;
TEST(gamesession, TurnControl) {
    reTurnControl con;
    ON_CALL(con, GetTime(true))
            .WillByDefault(Return(100));
    ON_CALL(con, GetTurn())
              .WillByDefault(Return(true));

    EXPECT_EQ(con.GetTime(true), 100);

}



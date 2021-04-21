#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "GameSession.h"

using ::testing::Return;
using ::testing::AtLeast;

class reTurnControl: public iTurnControl {
public:
    MOCK_METHOD(void, StopTimer, ());
    MOCK_METHOD(void, EnableTimer, ());
    MOCK_METHOD(void, SwitchTurn, ());
    MOCK_METHOD(time_t, GetTime, (bool Turn));
    MOCK_METHOD(bool, GetTurn, ());
};


TEST(gamesession, TurnControl) {
    reTurnControl control;
    ON_CALL(control, GetTime(true))
            .WillByDefault(Return(100));
    ON_CALL(control, GetTurn())
              .WillByDefault(Return(true));
    EXPECT_EQ(control.GetTurn(), true);
    EXPECT_EQ(control.GetTime(true), 100);
    GameSession session(&control);
    EXPECT_EQ(session.GetTime(), 100);

}



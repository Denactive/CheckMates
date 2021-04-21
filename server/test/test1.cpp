#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "GameSession.h"



class reTurnControl {
public:
    MOCK_METHOD(time_t, GetTime, (bool Turn) );
    MOCK_METHOD(bool, GetTurn, () );
};

using ::testing::Return;
TEST(gamesession, TurnControl) {
    reTurnControl control;
    iTurnControl* c = (iTurnControl*)&control;
    GameSession Session(*(c));
    ON_CALL(control, GetTime(true))
            .WillByDefault(Return(100));
    ON_CALL(control, GetTurn())
              .WillByDefault(Return(true));
    EXPECT_EQ(Session.control.GetTime(Session.control.GetTurn()), 100);

}



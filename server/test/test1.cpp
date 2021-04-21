#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "GameSession.h"


class reTurnControl: public iTurnControl {
private:
    bool Turn;
    time_t Timer1;
    time_t Timer2;
    void SwitchTurn();
    void EnableTimer();
    virtual void StopTimer();
public:
    MOCK_METHOD(time_t, GetTime, (bool Turn) );
    MOCK_METHOD(bool, GetTurn, ());
};


using ::testing::Return;
TEST(gamesession, TurnControl) {
    reTurnControl control;
    iTurnControl* c = &control;
    GameSession Session(c);
    ON_CALL(control, GetTime(true))
            .WillByDefault(Return(100));
    ON_CALL(control, GetTurn())
              .WillByDefault(Return(true));

    EXPECT_EQ(Session.control->GetTime(Session.control->GetTurn()), 100);

}



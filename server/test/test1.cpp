#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "GameSession.h"
#include "reTurnControl.h"
#include "rePlayer.h"

using ::testing::Return;
using ::testing::AtLeast;



TEST(gamesession, Mock) {

    #include "OnCallPlayer.h"
    EXPECT_EQ(player.try_move(), true);
    EXPECT_EQ(player.is_check(), false);
    EXPECT_EQ(player.is_mate(), false);
    EXPECT_EQ(player.is_stalemate(), false);
    EXPECT_EQ(player.all_available_Moves(), vec);
    EXPECT_EQ(player.GetUserId(), 0);
     #include "OnCallTurn.h"
    EXPECT_EQ(control.GetTurn(), true);
    EXPECT_EQ(control.GetTime(true), 100);

    GameSession session(&control, &player);
    EXPECT_EQ(session.GetTime(), 100);
    EXPECT_EQ(session.MakeMove(), true);
}



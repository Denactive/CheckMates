#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "GameSession.h"
#include "reTurnControl.h"
#include "rePlayer.h"

using ::testing::Return;
using ::testing::AtLeast;



TEST(gamesession, Mock) {
    #include "OnCallPlayer.h"
    #include "OnCallTurn.h"
    GameSession session(&control, &player);
    EXPECT_EQ(session.wPlayer->try_move(), true);
    EXPECT_EQ(session.wPlayer->is_check(), false);
    EXPECT_EQ(session.wPlayer->is_mate(), false);
    EXPECT_EQ(session.wPlayer->is_stalemate(), false);
    EXPECT_EQ(session.wPlayer->all_available_Moves(), vec);
    EXPECT_EQ(session.wPlayer->GetUserId(), 0);
    EXPECT_EQ(session.control->GetTurn(), true);
    EXPECT_EQ(session.control->GetTime(true), 100);
    EXPECT_EQ(session.GetTime(), 100);
    EXPECT_EQ(session.MakeMove(), true);
    EXPECT_EQ(session.wPlayer->GetUserId(), 0);
}



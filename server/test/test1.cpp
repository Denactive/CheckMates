#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "GameSession.h"
#include "reTurnControl.h"
#include "rePlayer.h"

using ::testing::Return;
using ::testing::AtLeast;



TEST(gamesession, Player) {
    rePlayer player;
    ON_CALL(player, try_move())
            .WillByDefault(Return(true));
    ON_CALL(player, is_check())
            .WillByDefault(Return(false));
    ON_CALL(player, is_mate())
            .WillByDefault(Return(false));
    ON_CALL(player, is_stalemate())
            .WillByDefault(Return(false));
    ON_CALL(player, GetUserId())
            .WillByDefault(Return(0));

    std::vector<std::string> vec;
    vec.push_back("new");
    ON_CALL(player, all_available_Moves())
            .WillByDefault(Return(vec));
    EXPECT_EQ(player.try_move(), true);
    EXPECT_EQ(player.is_check(), false);
    EXPECT_EQ(player.is_mate(), false);
    EXPECT_EQ(player.is_stalemate(), false);
    EXPECT_EQ(player.all_available_Moves(), vec);
    EXPECT_EQ(player.GetUserId(), 0);
    //GameSession session(&control);


}

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



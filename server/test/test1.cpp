#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "GameSession.h"
#include "reTurnControl.h"
#include "rePlayer.h"

using ::testing::Return;
using ::testing::AtLeast;


TEST(gamesession, Mock) {
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
    #include "OnCallTurn.h"
    DBServer log;
    GameSession session(&log, &control, &player);
    EXPECT_TRUE(session.wPlayer->try_move());
    EXPECT_FALSE(session.wPlayer->is_check());
    EXPECT_FALSE(session.wPlayer->is_mate());
    EXPECT_FALSE(session.wPlayer->is_stalemate());
    EXPECT_EQ(session.wPlayer->all_available_Moves(), vec);
    EXPECT_EQ(session.wPlayer->GetUserId(), 0);
    EXPECT_TRUE(session.control->GetTurn());
    EXPECT_EQ(session.control->GetTime(true), 100);
    EXPECT_EQ(session.GetTime(), 100);
    EXPECT_TRUE(session.MakeMove());
    EXPECT_EQ(session.wPlayer->GetUserId(), 0);
    EXPECT_EQ(session.log->query("new"), "new");
    ChessBoard newboard;
    EXPECT_EQ(session.board.get_board(), newboard.get_board());
    session.board.set_board();
    std::vector<char> B;
    B.push_back('P');
    EXPECT_EQ(session.board.get_board(), B);
    EXPECT_EQ(session.history.PrepareLog(), vec);
    EXPECT_EQ(session.history.PrepareLog(), vec);
    session.log->write("Hello, world!");
    EXPECT_EQ(session.log->read(), "Hello, world!");
}



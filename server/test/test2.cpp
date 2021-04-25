#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "GameSession.h"
#include "reChessPiece.h"

using ::testing::Return;
using ::testing::AtLeast;

TEST(Player, Mock) {
    ChessBoard board;
    reChessPiece piece;
    std::vector<ChessPiece*> testpiece;
    testpiece.push_back(&piece);
    Player player(board, testpiece);
    std::vector<std::string> vec;
    vec.push_back("new");
    ON_CALL(piece, available_moves())
            .WillByDefault(Return(vec));
    ON_CALL(piece, is_check())
            .WillByDefault(Return(false));
    ON_CALL(piece, is_mate())
            .WillByDefault(Return(false));
    ON_CALL(piece, is_stalemate())
            .WillByDefault(Return(true));

    EXPECT_FALSE(player.is_check());
    EXPECT_TRUE(player.is_stalemate());
    EXPECT_FALSE(player.is_mate());
    EXPECT_EQ(player.pieces[0]->available_moves(), vec);
}
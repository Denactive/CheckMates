#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "GameSession.h"
#include "reChessPiece.h"

using ::testing::Return;
using ::testing::AtLeast;




TEST(Player, Mock) {
    ChessBoard board;
    reChessPiece piece[16] = {};
    Player player(board, piece);
    std::vector<std::string> vec;
    vec.push_back("new");
    ON_CALL(piece[0], available_moves())
            .WillByDefault(Return(vec));

    EXPECT_EQ(player.pieces->available_moves(), vec);
}
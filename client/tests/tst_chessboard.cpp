#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include <string>
#include <vector>

#include <qt5/QtCore/QAbstractListModel>
#include <qt5/QtGui/QPixmap>

//using namespace testing;
//#include "../include/figures.h"
#include "../include/chessboard.h"
#include "reChessboard.h"

using ::testing::AtLeast;

TEST(chessboard, ok) {
    using ::testing::Return;
    using ::testing::AtLeast;

    MockChessBoard mock;
    std::vector<Cell> cells;
    King * king = nullptr;
    ChessBoard board;

    ON_CALL(mock, move).WillByDefault(Return(false));
    ON_CALL(mock, getSize).WillByDefault(Return(-1));
    ON_CALL(mock, isBorderOfBoard).WillByDefault(Return(false));
    ON_CALL(mock, isKingUnderMat(king)).WillByDefault(Return(false));

    EXPECT_EQ(board.move(1), true);
    EXPECT_EQ(board.getSize(), 8);
    EXPECT_EQ(board.isBorderOfBoard(1), false);
    EXPECT_EQ(board.isKingUnderMat(king), false);
}

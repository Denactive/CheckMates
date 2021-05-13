#ifndef RECHESSBOARD_H
#define RECHESSBOARD_H

#include "gmock/gmock.h"
#include "../include/chessboard.h"

class MockChessBoard : public IChessBoard {
public:
    MOCK_METHOD((bool), move, (int), (override));
    MOCK_CONST_METHOD0(getSize, size_t());
    MOCK_METHOD((bool), isBorderOfBoard, (const size_t), (override));
    MOCK_METHOD((bool), isKingUnderMat, (King *), (override));
    MOCK_METHOD((void), displayOnScreen, (), (override));
};

#endif // RECHESSBOARD_H

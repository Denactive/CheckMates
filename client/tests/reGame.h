#ifndef REGAME_H
#define REGAME_H

#include "gmock/gmock.h"
#include "../graphics.h"

class MockWGame : public IGame {
public:
    MOCK_METHOD((void), drawChessBoard, (), (override));
    MOCK_METHOD((bool), moveFigure, (Figure *), (override));
    MOCK_METHOD((void), drawChat, (Chat *), (override));
    MOCK_METHOD((bool), sendMessage, (MyMessage *), (override));
    MOCK_METHOD((bool), offerDraw, (), (override));
    MOCK_METHOD((bool), surrender, (), (override));
};

#endif // REGAME_H

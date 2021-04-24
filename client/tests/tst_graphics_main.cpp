#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace testing;
using ::testing::Return;

#include "../graphics.h"

class MockGraphics : public IGraphics {
public:
    MOCK_METHOD((void), StartDraw, (), (override));
    MOCK_METHOD((void), cleanAll, (), (override));
    MOCK_METHOD((bool), getData, (char **, User*, Chat *), (override));
};

class MockWGame : public IGame {
public:
    MOCK_METHOD((void), drawChessBoard, (), (override));
    MOCK_METHOD((void), moveFigure, (Figure &), (override));
    MOCK_METHOD((void), drawChat, (Chat &), (override));
    MOCK_METHOD((void), sendMessage, (MyMessage &), (override));
    MOCK_METHOD((bool), offerDraw, (), (override));
    MOCK_METHOD((bool), surrender, (), (override));
};

class MockWMenu : public IMenu {
    MOCK_METHOD((void), drawMessages, (), (override));
    MOCK_METHOD((bool), drawFriends, (), (override));
    MOCK_METHOD((void), tapPlay, (), (override));
    MOCK_METHOD((void), turnOnMatching, (), (override));
    MOCK_METHOD((User*), chooseFriend, (), (override));
    MOCK_METHOD((Chat *), chooseChat, (), (override));
};

class MockWUserSettings : public IUserSettings {
    MOCK_METHOD((void), drawUserSettings, (), (override));
    MOCK_METHOD((bool), changeSettings, (), (override));
    MOCK_METHOD((void), saveSettings, (), (override));
    MOCK_METHOD((void), chooseUserPhoto, (), (override));
};

class MockWAuthorizer : public IAuthorizer {
    MOCK_METHOD((void), drawForm, (), (override));
    MOCK_METHOD((void), sendMessage, (MyMessage &), (override));
    MOCK_METHOD((bool), checkFromOnValid, (User &), (override));
};

class MockWChatMenu : public IChatMenu {
    MOCK_METHOD((void), drawMessages, (), (override));
    MOCK_METHOD((bool), sendMessage, (), (override));
    MOCK_METHOD((void), backToMenu, (), (override));
};

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;
using namespace testing;
using ::testing::Return;

#include "../graphics.h"
#include "reGraphics.h"
#include "reAuthorizer.h"
#include "reChatMenu.h"
#include "reGame.h"
#include "reMenu.h"
#include "reSettings.h"

TEST(Graphics, startDraw) {
    using ::testing::AtLeast;
    MockGraphics mock;
    User * user = nullptr;
    Chat * chats = nullptr;
    char ** chess = nullptr;

    Graphics ui;

    ON_CALL(mock, getData(chess, user, chats)).WillByDefault(Return(true));

    EXPECT_TRUE(ui.getData(chess, user, chats));
}

TEST(GameWindow, ok) {
    Figure *figure = nullptr;
    MyMessage *msg = nullptr;
    MockWGame mock;
    Game wgame;

    ON_CALL(mock, moveFigure(figure)).WillByDefault(Return(true));
    ON_CALL(mock, sendMessage(msg)).WillByDefault(Return(true));
    ON_CALL(mock, offerDraw()).WillByDefault(Return(true));
    ON_CALL(mock, surrender()).WillByDefault(Return(true));

    EXPECT_TRUE(wgame.moveFigure(figure));
    EXPECT_TRUE(wgame.sendMessage(msg));
    EXPECT_TRUE(wgame.offerDraw());
    EXPECT_TRUE(wgame.surrender());
}

TEST(MenuWindow, ok) {
    User * user = nullptr;
    Chat * chat = nullptr;
    MockWMenu mock;
    Menu menu;

    ON_CALL(mock, turnOnMatching()).WillByDefault(Return(true));
    ON_CALL(mock, tapPlay()).WillByDefault(Return(true));
    ON_CALL(mock, chooseFriend()).WillByDefault(Return(nullptr));
    ON_CALL(mock, chooseChat()).WillByDefault(Return(nullptr));

    EXPECT_TRUE(menu.turnOnMatching());
    EXPECT_TRUE(menu.tapPlay());
    EXPECT_EQ(menu.chooseChat(), chat);
    EXPECT_EQ(menu.chooseFriend(), user);
}

TEST(SettingsWindow, ok) {
    MockWUserSettings mock;
    UserSettings usrStgs;

    ON_CALL(mock, changeSettings()).WillByDefault(Return(true));
    ON_CALL(mock, saveSettings()).WillByDefault(Return(true));
    ON_CALL(mock, chooseUserPhoto()).WillByDefault(Return(true));

    EXPECT_TRUE(usrStgs.changeSettings());
    EXPECT_TRUE(usrStgs.saveSettings());
    EXPECT_TRUE(usrStgs.chooseUserPhoto());
}

TEST(AuthorizerWindow, ok) {
    MockWAuthorizer mock;
    MyMessage * msg = nullptr;
    User * user = nullptr;
    Authorizer authorizer;

    ON_CALL(mock, sendMessage(msg)).WillByDefault(Return(true));
    ON_CALL(mock, checkFromOnValid(user)).WillByDefault(Return(true));

    EXPECT_TRUE(authorizer.sendMessage(msg));
    EXPECT_TRUE(authorizer.checkFromOnValid(user));
}

TEST(ChatMenu, ok) {
    MockWChatMenu mock;
    ChatMenu menu;

    ON_CALL(mock, sendMessage()).WillByDefault(Return(true));
    ON_CALL(mock, backToMenu()).WillByDefault(Return(true));

    EXPECT_TRUE(menu.sendMessage());
    EXPECT_TRUE(menu.backToMenu());
}


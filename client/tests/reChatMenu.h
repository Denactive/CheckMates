#ifndef RECHATMENU_H
#define RECHATMENU_H

#include "gmock/gmock.h"
#include "../graphics.h"

class MockWChatMenu : public IChatMenu {
public:
    MOCK_METHOD((void), drawUserSettings, (), (override));
    MOCK_METHOD((void), drawMessages, (), (override));
    MOCK_METHOD((bool), sendMessage, (), (override));
    MOCK_METHOD((bool), backToMenu, (), (override));
};

#endif // RECHATMENU_H

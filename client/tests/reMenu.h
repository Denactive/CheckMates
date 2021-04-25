#ifndef REMENU_H
#define REMENU_H

#include "gmock/gmock.h"
#include "../graphics.h"

class MockWMenu : public IMenu {
public:
    MOCK_METHOD((void), drawMessages, (), (override));
    MOCK_METHOD((void), drawFriends, (), (override));
    MOCK_METHOD((bool), tapPlay, (), (override));
    MOCK_METHOD((bool), turnOnMatching, (), (override));
    MOCK_METHOD((User*), chooseFriend, (), (override));
    MOCK_METHOD((Chat *), chooseChat, (), (override));
};

#endif // REMENU_H

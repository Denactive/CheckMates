#ifndef RESETTINGS_H
#define RESETTINGS_H

#include "gmock/gmock.h"
#include "../graphics.h"

class MockWUserSettings : public IUserSettings {
public:
    MOCK_METHOD((void), drawUserSettings, (), (override));
    MOCK_METHOD((bool), changeSettings, (), (override));
    MOCK_METHOD((bool), saveSettings, (), (override));
    MOCK_METHOD((bool), chooseUserPhoto, (), (override));
};

#endif // RESETTINGS_H

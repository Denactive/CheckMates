#ifndef REAUTHORIZER_H
#define REAUTHORIZER_H

#include "gmock/gmock.h"
#include "../graphics.h"

class MockWAuthorizer : public IAuthorizer {
public:
    MOCK_METHOD((void), drawForm, (), (override));
    MOCK_METHOD((bool), sendMessage, (MyMessage *), (override));
    MOCK_METHOD((bool), checkFromOnValid, (User *), (override));
};

#endif // REAUTHORIZER_H

#ifndef REGRAPHICS_H
#define REGRAPHICS_H

#include "gmock/gmock.h"
#include "../graphics.h"

class MockGraphics : public IGraphics {
public:
    MOCK_METHOD((void), StartDraw, (), (override));
    MOCK_METHOD((void), cleanAll, (), (override));
    MOCK_METHOD((bool), getData, (char **, User*, Chat *), (override));
};

#endif // REGRAPHICS_H

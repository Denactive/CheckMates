#ifndef CHECKMATES_LOGGER_H
#define CHECKMATES_LOGGER_H
#include "GameSession.h"

class iLogger {
public:
    virtual void log(std::string) = 0;
};

class Logger : public iLogger  {
public:
    void log(std::string);
};
#endif //CHECKMATES_LOGGER_H

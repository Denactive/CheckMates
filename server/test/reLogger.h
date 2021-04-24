//
// Created by denactive on 23.04.2021.
//

#ifndef SERVER_RELOGGER_H
#define SERVER_RELOGGER_H

class reLogger : public ILogger  {
public:
    MOCK_METHOD(void, log, (std::string), (override));
};

#endif //SERVER_RELOGGER_H

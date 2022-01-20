//
// Created by denactive on 23.04.2021.
//

#ifndef SERVER_RELOGGER_H
#define SERVER_RELOGGER_H

class reLogger : public ILogger  {
public:
    MOCK_METHOD(void, log, (const std::string&), (override));
    MOCK_METHOD(void, set_log_directory, (const std::string&), (override));
};

#endif //SERVER_RELOGGER_H

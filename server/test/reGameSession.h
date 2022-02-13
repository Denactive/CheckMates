//
// Created by denactive on 25.04.2021.
//

#ifndef SERVER_REGAMESESSION_H
#define SERVER_REGAMESESSION_H

class reGameSession {
public:
    MOCK_METHOD(std::vector <std::string>, all_available_Moves, ());
    MOCK_METHOD(void, SetBoard, ());
    MOCK_METHOD(bool, MakeMove, ());
    MOCK_METHOD(void, CreateLog, ());
    MOCK_METHOD(void, DrawHandler, ());
    MOCK_METHOD(std::string, GetStatus, ());
    MOCK_METHOD(void, run, ());
    MOCK_METHOD(time_t, GetTime, ());
    MOCK_METHOD(void, GiveUpHandler, ());
    MOCK_METHOD(void, StalemateHandler, ());
};
#endif //SERVER_REGAMESESSION_H

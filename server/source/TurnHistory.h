//
// Created by yura11011 on 15.04.2021.
//

#ifndef CHECKMATES_TURNHISTORY_H
#define CHECKMATES_TURNHISTORY_H
#include <GameSession.h>

class TurnHistory {
public:
    void logTurn();
    void  addPiece();
    std::vector<std::string> PrepareLog() {
        std::vector<std::string> vec;
        vec.push_back("new");
        return vec;
    }
private:
    std::vector<char> piecesCaptured;
    std::vector<std::string> turnHistory;
};

#endif //CHECKMATES_TURNHISTORY_H

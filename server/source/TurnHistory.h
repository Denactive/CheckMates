//
// Created by yura11011 on 15.04.2021.
//

#ifndef CHECKMATES_TURNHISTORY_H
#define CHECKMATES_TURNHISTORY_H
#include <GameSession.h>

class TurnHistory {
public:
    std::vector<char> piecesCaptured;
    std::vector<std::string> turnHistory;
    void logTurn();
    void  addPiece();
};

#endif //CHECKMATES_TURNHISTORY_H

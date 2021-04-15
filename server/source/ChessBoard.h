//
// Created by yura11011 on 14.04.2021.
//

#ifndef CHECKMATES_CHESSBOARD_H
#define CHECKMATES_CHESSBOARD_H

#include "GameSession.h"


class ChessBoard {
private:
    std::vector<char> board;
public:
    void get_board();
    void chess_board();
};


#endif //CHECKMATES_CHESSBOARD_H

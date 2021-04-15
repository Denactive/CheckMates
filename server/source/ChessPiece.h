//
// Created by yura11011 on 14.04.2021.
//

#ifndef CHECKMATES_CHESSPIECE_H
#define CHECKMATES_CHESSPIECE_H
#include "GameSession.h"

class IChessPiece {
public:
virtual void move() = 0;
virtual std::vector<std::string> available_moves();
virtual void capture_piece();
}


#endif //CHECKMATES_CHESSPIECE_H

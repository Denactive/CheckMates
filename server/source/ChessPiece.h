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
};

class King :public IChessPiece {
private:
    char position[2];
    std::vector<std::string> avail_moves;
public:
    void move();
    void is_check();
    void castling();
    std::vector<std::string> available_moves();
    void capture_piece();
};

class Queen :public IChessPiece {
private:
    char position[2];
    std::vector<std::string> avail_moves;
public:
    void move();
    void is_check();
    void is_captured();
    std::vector<std::string> available_moves();
    void capture_piece();
};

class Bishop :public IChessPiece {
private:
    char position[2];
    std::vector<std::string> avail_moves;
public:
    void move();
    void is_check();
    void is_captured();
    std::vector<std::string> available_moves();
    void capture_piece();
};

class Rook :public IChessPiece {
private:
    char position[2];
    std::vector<std::string> avail_moves;
public:
    void move();
    void is_check();
    void is_captured();
    std::vector<std::string> available_moves();
    void capture_piece();
};

class Knight :public IChessPiece {
private:
    char position[2];
    std::vector<std::string> avail_moves;
public:
    void move();
    void is_check();
    void is_captured();
    std::vector<std::string> available_moves();
    void capture_piece();
};

class Pawn :public IChessPiece {
private:
    char position[2];
    std::vector<std::string> avail_moves;
public:
    void move();
    void is_check();
    void is_captured();
    std::vector<std::string> available_moves();
    void capture_piece()
    void is_promoted();
};
#endif //CHECKMATES_CHESSPIECE_H

//
// Created by yura11011 on 14.04.2021.
//

#ifndef CHECKMATES_CHESSPIECE_H
#define CHECKMATES_CHESSPIECE_H
#include "GameSession.h"

class ChessPiece {
public:
virtual void move() = 0;
virtual std::vector<std::string> available_moves() = 0;
virtual void capture_piece() = 0;
};

class King :public ChessPiece {
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

class Queen :public ChessPiece {
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

class Bishop :public ChessPiece {
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

class Rook :public ChessPiece {
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

class Knight :public ChessPiece {
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

class Pawn :public ChessPiece {
private:
    char position[2];
    std::vector<std::string> avail_moves;
public:
    void move();
    void is_check();
    void is_captured();
    std::vector<std::string> available_moves();
    void capture_piece();
    void is_promoted();
};
#endif //CHECKMATES_CHESSPIECE_H

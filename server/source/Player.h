#pragma once

#include "GameSession.h"

class iPlayer {

public:
    virtual std::vector<std::string> all_available_Moves() = 0;
    virtual bool try_move() = 0;
    virtual bool is_check() = 0;
    virtual bool is_mate() = 0;
    virtual bool is_stalemate() = 0;
    virtual size_t GetUserId() = 0;
    virtual void set_pieces() = 0;
};

class Player: public iPlayer {
private:
    ChessBoard& board;
   // User user;

public:
    Player(ChessBoard& board, ChessPiece* pieces):board(board), pieces(pieces) {};
    ChessPiece* pieces;
    std::vector<std::string> all_available_Moves() {
        std::vector<std::string> vec;
        return vec;
    };

    bool try_move() {return true;};
    bool is_check(){return true;};
    bool is_mate(){return true;};
    bool is_stalemate(){return true;};
    size_t GetUserId(){return 0;};
    void set_pieces(){};
};


#pragma once

#include "User.h"
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
    User user;
    ChessPiece pieces[16];
public:
    Player();
    std::vector<std::string> all_available_Moves();
    bool try_move();
    bool is_check();
    bool is_mate();
    bool is_stalemate();
    size_t GetUserId();
    void set_pieces();
};


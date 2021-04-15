#ifndef CHECKMATES_PLAYER_H
#define CHECKMATES_PLAYER_H
#include "User.h"
#include "ChessPiece.h"

class iPlayer {

public:
    virtual std::vector<std::string> all_available_Moves() = 0;
    virtual void try_move() = 0;
    virtual void is_check() = 0;
    virtual void is_mate() = 0;
    virtual void is_statemate() = 0;
    virtual User get_user() = 0;
    virtual void set_pieces() = 0;
};

class Player: public iPlayer {
private:
    ChessBoard& board;
    User& user;
    ChessPiece pieces[16];
public:
    std::vector<std::string> all_available_Moves();
    void try_move();
    void is_check();
    void is_mate();
    void is_statemate();
    User get_user();
    void set_pieces();
};


#endif //CHECKMATES_PLAYER_H

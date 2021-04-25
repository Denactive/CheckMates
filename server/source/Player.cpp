#include "GameSession.h"
#include "Player.h"

Player::Player(ChessBoard& board, std::vector<ChessPiece*> pieces, User user):board(board), pieces(pieces) {};

std::vector<std::string> Player::all_available_Moves() {
    std::vector<std::string> vec;
    vec.push_back("e2-e4");
    return vec;
};

bool Player::is_check(){
    return pieces[0]->is_check();
};

bool Player::is_mate(){
    return pieces[0]->is_mate();
};
bool Player::is_stalemate(){
    return pieces[0]->is_stalemate();
};
size_t Player::GetUserId(){
    return 0;
};
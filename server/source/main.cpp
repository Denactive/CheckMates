#include <iostream>
#include <vector>
#include "Chesspiece.h"
#include "Player.h"
#include "GameSession.h"

int main() {
    ChessBoard board;
    board.set_board();
    Player player1(board, true);
    Player player2(board, false);
    TurnControl control;
    GameSession A(control, player1, player2);
    A.run();

    return 0;
}

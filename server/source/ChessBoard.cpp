#include "ChessBoard.h"

void ChessBoard::set_board() {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < N; ++j) {
        board[i][j] = White;
    }
    }
    for (int i = N - 2; i < N ; ++i) {
        for (int j = 0; j < N; ++j) {
            board[i][j] = Black;
        }
    }

    for (int i = 2; i < N - 2; ++i) {
        for (int j = 0; j < N; ++j) {
            board[i][j] = Empty;
        }
    }
}

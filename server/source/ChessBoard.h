
#ifndef CHESS_CHESSBOARD_H
#define CHESS_CHESSBOARD_H
#define N 8

#include "array"
#include "iostream"

enum cell {
    Empty,
    White,
    Black
};

class ChessBoard {
private:
    std::array<std::array<cell, N>, N> board;
public:
    std::array<std::array<cell, N>, N> get_board() {
        return board;
    };
    void set_board();
    void move_chess(std::array<size_t, N/2> turn) {
        cell temp  = board[turn[0]][turn[1]];
        board[turn[0]][turn[1]] = Empty;
        board[turn[2]][turn[3]] = temp;
    }
    void set(cell Cell, size_t i, size_t j) {
        board[i][j] = Cell;
    }
    void draw_board() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                std::cout << board[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }
};
#endif //CHESS_CHESSBOARD_H

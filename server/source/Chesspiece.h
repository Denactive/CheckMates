//
// Created by yura11011 on 10.05.2021.
//

#ifndef CHESS_CHESSPIECE_H
#define CHESS_CHESSPIECE_H
#include <memory>
#include <vector>
#include <string>
#include <array>
#include <set>
#include "ChessBoard.h"
#define M 4
#define K 2


class ChessPiece {
public:
    virtual ~ChessPiece() {}
    virtual void move(std::array<size_t, M> turn) = 0;
    virtual const size_t* where() = 0;
    virtual std::vector<std::array<size_t, M>> available_moves() = 0;
    virtual std::set<std::array<size_t, K>> threatens() = 0;
    virtual void is_captured() = 0;
    virtual void try_capture() = 0;
};

class King : public ChessPiece {
private:
    size_t position[2];
    std::set<std::array<size_t, K>> threat;
    std::vector<std::array<size_t, M>> avail_moves;
    std::set<std::array<size_t, K>> enemy_threats;
public:
    bool castle;
    void Update_King(std::set<std::array<size_t, K>> input) ;
    const size_t* where()  { return position;}
    King(size_t i, size_t j, std::shared_ptr<ChessBoard> board);
    ~King();
    void move(std::array<size_t, M> turn) {
        position[0] = turn[2];
        position[1] = turn[3];
      //  std::cout << position[0]<< position[1]<< turn[2]<< turn[3];
    }
    std::shared_ptr<ChessBoard> board;
    void castling();
    std::vector<std::array<size_t, M>> available_moves();
    std::set<std::array<size_t, K>> threatens();
    void is_captured() {};
    void try_capture() {
        position[0] = 10;
        position[1] = 10;
    };
};

class Queen :public ChessPiece {
private:
    size_t position[2];
    std::set<std::array<size_t, K>> threat;
    std::vector<std::array<size_t, M>> avail_moves;
public:
    const size_t* where()  { return position;}
    Queen(size_t i, size_t j, std::shared_ptr<ChessBoard> board): board(board) {
        position[0] = i;
        position[1] = j;
    };
    void move(std::array<size_t, M> turn) {
        position[0] = turn[2];
        position[1] = turn[3];
    }
    std::shared_ptr<ChessBoard> board;
    std::vector<std::array<size_t, M>> available_moves();
    std::set<std::array<size_t, K>> threatens();
    void is_captured() {
        position[0] = 9;
        position[1] = 9;
    };
    void try_capture() {
        position[0] = 10;
        position[1] = 10;
    };
    ~Queen() {};
};

class Bishop :public ChessPiece {
private:
    size_t position[2];
    std::vector<std::array<size_t, M>> avail_moves;
    std::set<std::array<size_t, K>> threat;
public:
    const size_t* where()  { return position;}
    Bishop(size_t i, size_t j, std::shared_ptr<ChessBoard> board): board(board) {
        position[0] = i;
        position[1] = j;
    }
    void move(std::array<size_t, M> turn) {
        position[0] = turn[2];
        position[1] = turn[3];
    }
    std::shared_ptr<ChessBoard> board;
    std::vector<std::array<size_t, M>> available_moves();
    std::set<std::array<size_t, K>> threatens();
    void is_captured() {
        position[0] = 9;
        position[1] = 9;
    };
    void try_capture() {
        position[0] = 10;
        position[1] = 10;
    };
};

class Rook :public ChessPiece {
private:
    size_t position[2];
    std::set<std::array<size_t, K>> threat;
    std::vector<std::array<size_t, M>> avail_moves;
public:
    const size_t* where()  { return position;}
    Rook(size_t i, size_t j, std::shared_ptr<ChessBoard> board)
        : board(board) {
        position[0] = i;
        position[1] = j;
    };
    void move(std::array<size_t, M> turn) {
        position[0] = turn[2];
        position[1] = turn[3];
    }
    std::shared_ptr<ChessBoard> board;
    std::vector<std::array<size_t, M>> available_moves();
    std::set<std::array<size_t, K>> threatens();
    void is_captured() {
        position[0] = 9;
        position[1] = 9;
    };
    void try_capture() {
        position[0] = 10;
        position[1] = 10;
    };
};

class Knight :public ChessPiece {
private:
    size_t position[2];
    std::set<std::array<size_t, K>> threat;
    std::vector<std::array<size_t, M>> avail_moves;
public:
    const size_t* where()  { return position;}
    Knight(size_t i, size_t j, std::shared_ptr<ChessBoard> board): board(board) {
        position[0] = i;
        position[1] = j;
    };
    void move(std::array<size_t, M> turn) {
        position[0] = turn[2];
        position[1] = turn[3];
    }
    std::shared_ptr<ChessBoard> board;
    std::vector<std::array<size_t, M>> available_moves();
    std::set<std::array<size_t, K>> threatens();
    void is_captured() {
        position[0] = 9;
        position[1] = 9;
    }
    void try_capture() {
        position[0] = 10;
        position[1] = 10;
    };
};

class Pawn :public ChessPiece {
private:
    bool white;
    size_t position[2];
    std::set<std::array<size_t, K>>threat;
    std::vector<std::array<size_t, M>>avail_moves;
public:
    const size_t* where()  { return position;}
    Pawn(size_t i, size_t j, std::shared_ptr<ChessBoard> board): board(board) {
        position[0] = i;
        position[1] = j;
        if (i == 1) {
            white = true;
        } else {
            white = false;
        }
    };

    void move(std::array<size_t, M> turn) {
        position[0] = turn[2];
        position[1] = turn[3];
    }

    std::shared_ptr<ChessBoard> board;
    std::vector<std::array<size_t, M>> available_moves();
    std::set<std::array<size_t, K>> threatens();
    void is_captured() {
        position[0] = 9;
        position[1] = 9;
    };
    void try_capture() {
        position[0] = 10;
        position[1] = 10;
    };
    void is_promoted();
};


#endif //CHESS_CHESSPIECE_H

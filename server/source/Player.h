
#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H
#include <vector>
#include <string>

#include "Chesspiece.h"
#include "ChessBoard.h"



class IPlayer {
public:
    std::array<ChessPiece*, 2*N> pieces;
    virtual std::vector<std::array<size_t, M>>  all_available_Moves() = 0;
    virtual void move(std::array<size_t, M> turn) = 0;
    virtual void is_captured(std::array<size_t, M> turn) = 0;
    virtual size_t try_capture(std::array<size_t, M> turn) = 0;
    virtual size_t GetUserId() = 0;
    virtual void set_pieces() = 0;
    virtual void print_pos() = 0;
    virtual ChessBoard& getboard () = 0;
    virtual void KingUpdate(std::set<std::array<size_t, K>> thr) = 0;
    virtual const size_t* where() = 0;
    virtual std::vector<std::array<size_t, M>>& access() = 0;
    virtual std::set<std::array<size_t, K>> all_threatens() = 0;
};

class Player: public IPlayer {
private:
    bool wb;
    std::vector<std::array<size_t, M>> moves;
    std::set<std::array<size_t, K>> threats;
    ChessBoard& board;
    King* king;
public:
    size_t try_capture(std::array<size_t, M> turn);
    std::vector<std::array<size_t, M>>& access() {
        std::vector<std::array<size_t, M>>& temp = moves;
        return temp;
    }
    ChessBoard& getboard () {
        return board;
    };
    void KingUpdate(std::set<std::array<size_t, K>> thr) {
        king->Update_King(thr);
    }
    const size_t* where() {
        return king->where();
    }
    Player(ChessBoard& board, bool wb);
    std::array<ChessPiece*, 2*N> pieces;
    std::vector<std::array<size_t, M>>  all_available_Moves();
    std::set<std::array<size_t, K>>  all_threatens();
    void move(std::array<size_t, M> turn);
    void is_captured(std::array<size_t, M> turn);
    void print_pos();
    size_t GetUserId();
    void set_pieces();
};

#endif //CHESS_PLAYER_H

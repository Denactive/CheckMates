
#ifndef CHESS_PLAYER_H
#define CHESS_PLAYER_H
#include <vector>
#include <string>


#include "User.h"
//#include "GameSession.h"
#include "ChessBoard.h"
#include "Chesspiece.h"



class IPlayer {
public:
    virtual std::shared_ptr<WebSocketSession> Get_Session() = 0;
    std::array<ChessPiece*, 2*N> pieces;
    virtual std::vector<std::array<size_t, M>>  all_available_Moves() = 0;
    virtual void move(std::array<size_t, M> turn) = 0;
    virtual void is_captured(std::array<size_t, M> turn) = 0;
    virtual size_t try_capture(std::array<size_t, M> turn) = 0;
    virtual std::shared_ptr<IUser> get_user() = 0;
    virtual void set_pieces() = 0;
    virtual void flag_castl(std::array<size_t, M> turn) = 0;
    virtual void print_pos() = 0;
    virtual std::shared_ptr<ChessBoard> getboard () = 0;
    virtual void KingUpdate(std::set<std::array<size_t, K>> thr) = 0;
    virtual const size_t* where() = 0;
    virtual std::vector<std::array<size_t, M>>& access() = 0;
    virtual std::set<std::array<size_t, K>> all_threatens() = 0;
};

class Player: public IPlayer {
private:
    bool wb = false;
    std::vector<std::array<size_t, M>> moves;
    std::set<std::array<size_t, K>> threats;
    std::shared_ptr<ChessBoard> board;
    King* king = NULL;
    std::shared_ptr<IUser> user_;

public:
    std::shared_ptr<WebSocketSession> Get_Session() {
        return session;
    };
    std::shared_ptr<WebSocketSession> session;
    void flag_castl(std::array<size_t, M> turn);

    Player(std::shared_ptr<IUser> user, std::shared_ptr<ChessBoard> board, bool wb)
        : user_(user)
        , board(board)
        , king(nullptr), wb(wb)
    {
        Player::set_pieces();
        king = static_cast<King*>(pieces[4]);
    };

    size_t try_capture(std::array<size_t, M> turn);

    std::vector<std::array<size_t, M>>& access() {
        std::vector<std::array<size_t, M>>& temp = moves;
        return temp;
    }

    std::shared_ptr<ChessBoard> getboard () { return board; }

    void KingUpdate(std::set<std::array<size_t, K>> thr) { king->Update_King(thr); }

    const size_t* where() { return king->where(); }

    std::array<ChessPiece*, 2*N> pieces;
    std::vector<std::array<size_t, M>>  all_available_Moves();
    std::set<std::array<size_t, K>>  all_threatens();
    void move(std::array<size_t, M> turn);
    void is_captured(std::array<size_t, M> turn);
    void print_pos();
    std::shared_ptr<IUser> get_user() override { return user_; }
    void set_pieces();
};

#endif //CHESS_PLAYER_H

//
// Created by yura11011 on 10.05.2021.
//

#ifndef CHESS_GAMESESSION_H
#define CHESS_GAMESESSION_H
#include <vector>
#include <string>

#include "Chesspiece.h"
#include "ChessBoard.h"
#include "Player.h"
#include "TurnControl.h"

struct GInfo{
    bool isPlayer;
    bool isGame;
    char isVictory;
    bool isCheck;
};

class IGameSession {
public:
    virtual ~IGameSession() {};
    virtual void CreateLog() = 0;
    virtual std::array<size_t, M> GetTurn() = 0;
    virtual time_t GetTime() = 0;
    virtual void run() = 0;
    virtual int run_turn() = 0;;
    virtual bool is_check(class IPlayer* you, IPlayer* enemy) = 0;
    virtual bool is_mate(IPlayer* you, IPlayer* enemy)= 0;
    virtual bool is_stalemate(IPlayer* you, IPlayer* enemy)= 0;
    virtual void send_move(std::array<size_t, M> turn) = 0;
    virtual void send_info(GInfo info) = 0;
};

class GameSession: public IGameSession {
public:

  //  explicit GameSession(IDBServer* log, ITurnControl* control, IPlayer* player);
    GameSession(ITurnControl& control, IPlayer& player1, IPlayer& player2);
    GameSession() = default;
    void CreateLog();
    bool is_check(IPlayer* you, IPlayer* enemy);
    bool is_mate(IPlayer* you, IPlayer* enemy);
    bool is_stalemate(IPlayer* you, IPlayer* enemy);
    bool GameStatus();
    void run();
    int run_turn();
    time_t GetTime();
    ~GameSession() = default;
    std::array<size_t, M> GetTurn();
    void print_moves (IPlayer* you);
    void move(IPlayer* you, IPlayer* enemy, std::array<size_t, M> turn);
    void send_move(std::array<size_t, M> turn) {
        std::cout <<"\n"<< turn[0] << turn[1] << turn[2] << turn[3]<<"\n";
    }
    void send_info(GInfo info) {
        std::cout <<"\n"<< info.isPlayer << info.isGame << info.isVictory << info.isCheck <<"\n";
    }
    void try_move(IPlayer* you, IPlayer* enemy);
   // IDBServer* log;
    ITurnControl& control;
    IPlayer& wPlayer;
    IPlayer& bPlayer;
    ChessBoard& board;
    //TurnHistory history;
private:
    GInfo info;
};



#endif //CHESS_GAMESESSION_H

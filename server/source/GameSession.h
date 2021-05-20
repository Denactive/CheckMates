//
// Created by yura11011 on 10.05.2021.
//

#ifndef CHESS_GAMESESSION_H
#define CHESS_GAMESESSION_H

#include "ChessBoard.h"
#include "Player.h"

#include <vector>
#include <string>
#include <array>

//class IPlayer;

struct GInfo {
    bool isPlayer;
    bool isGame;
    char isVictory;
    bool isCheck;
    std::array<size_t, M> turn;
};

class IGameSession {
public:
    virtual ~IGameSession() {};
    virtual void CreateLog() = 0;
    virtual time_t GetTime() = 0;
    virtual int run_turn(std::array<size_t, M>) = 0;
    virtual void setup() = 0;
    virtual bool is_check(std::shared_ptr<IPlayer>, std::shared_ptr<IPlayer>) = 0;
    virtual bool is_mate(std::shared_ptr<IPlayer> you, std::shared_ptr<IPlayer> enemy)= 0;
    virtual bool is_stalemate(std::shared_ptr<IPlayer> you, std::shared_ptr<IPlayer> enemy)= 0;
    virtual void send_move(std::array<size_t, M> turn) = 0;
    virtual GInfo send_info() = 0;
    virtual int prepare_turn() = 0;
};

class GameSession: public IGameSession {
public:

    std::shared_ptr<IPlayer> wPlayer;
    std::shared_ptr<IPlayer> bPlayer;
    std::shared_ptr<ChessBoard> board;
    size_t token = 0;

    GameSession (
        std::shared_ptr<IUser> player1, std::shared_ptr<IUser> player2)
    {
        board = std::make_shared<ChessBoard>();

        wPlayer = std::make_shared<Player>(player1, board, true);
        bPlayer = std::make_shared<Player>(player2, board, false);
        setup();
    }

    GameSession() = delete;

    void CreateLog();
    int prepare_turn();
    bool is_check(std::shared_ptr<IPlayer> you, std::shared_ptr<IPlayer> enemy);
    bool is_mate(std::shared_ptr<IPlayer> you, std::shared_ptr<IPlayer> enemy);
    bool is_stalemate(std::shared_ptr<IPlayer> you, std::shared_ptr<IPlayer> enemy);
    bool GameStatus();
    std::array<size_t, M> GetTurn();
    int run_turn(std::array<size_t, M> turn);
    void setup();
    time_t GetTime();
    ~GameSession() = default;
    void print_moves (std::shared_ptr<IPlayer> you);

    void move(std::shared_ptr<IPlayer> you, std::shared_ptr<IPlayer> enemy, std::array<size_t, M> turn);

    void send_move(std::array<size_t, M> turn) {
        std::cout <<"\n"<< turn[0] << turn[1] << turn[2] << turn[3]<<"\n";
    }

    GInfo send_info() {
        std::cout <<"\n"<< info.isPlayer << info.isGame << info.isVictory << info.isCheck <<"\n";
        return info;
    }
    void try_move(std::shared_ptr<IPlayer> you, std::shared_ptr<IPlayer> enemy);

private:
    GInfo info;
};

struct GameSessionComparator {
    bool operator()(const std::shared_ptr<GameSession>& lhs, const std::shared_ptr<GameSession>& rhs) const {
        if (lhs->token < rhs->token)
            return true;
        else
            return false;
    }
};


#endif //CHESS_GAMESESSION_H

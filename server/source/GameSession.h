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
#include <map>

//class IPlayer;

struct GInfo {
    bool isPlayer;
    bool isGame;
    char isVictory;
    bool isCheck;
    std::array<size_t, M> turn;
};

typedef enum {
    ok,
    no_game_token,
    invalid_game_token,
    invalid_uid,
    no_prev_move,
    no_cur_move,
    invalid_format
} game_error_code;

std::string static game_error_code_to_string(const game_error_code& ec) {
    switch (ec) {
    case game_error_code::ok:
        return "OK";
        break;
    case game_error_code::invalid_format:
        return "Invalid Format";
        break;
    case game_error_code::invalid_game_token:
        return "Invalid Game Token";
        break;
    case game_error_code::invalid_uid:
        return "Invalid Uid";
        break;
    case game_error_code::no_cur_move:
        return "No Current Move";
        break;
    case game_error_code::no_game_token:
        return "No Game Token";
        break;
    case game_error_code::no_prev_move:
        return "No Previous Move";
        break;
    default:
        return "Unknown game error";
    }
}

void static print_game_error_code(const game_error_code& ec) {
    std::cout << game_error_code_to_string(ec) << std::endl;
}

struct Move {
    std::string game_token;
    uid id;
    int prev;
    int cur;
};

class IGameSession {
public:
    virtual ~IGameSession() {};
    virtual void CreateLog() = 0;
    virtual time_t GetTime() = 0;
    virtual int run_turn(std::array<size_t, M>) = 0;
    virtual void setup() = 0;
    virtual std::shared_ptr<IPlayer> you() = 0;
    virtual std::shared_ptr<IPlayer> enemy() = 0;
    virtual bool is_check(std::shared_ptr<IPlayer>, std::shared_ptr<IPlayer>) = 0;
    virtual bool is_mate(std::shared_ptr<IPlayer> you, std::shared_ptr<IPlayer> enemy)= 0;
    virtual bool is_stalemate(std::shared_ptr<IPlayer> you, std::shared_ptr<IPlayer> enemy)= 0;
    virtual void send_move(std::array<size_t, M> turn) = 0;
    virtual GInfo send_info() = 0;
    virtual int prepare_turn() = 0;
    virtual GameToken get_token() = 0;
    virtual std::string get_token_string() = 0;
};

class GameSession: public IGameSession {
public:

    std::shared_ptr<IPlayer> wPlayer;
    std::shared_ptr<IPlayer> bPlayer;
    std::shared_ptr<ChessBoard> board;
    

    GameSession(
        std::shared_ptr<IUser> player1, std::shared_ptr<IUser> player2)
        : token_(std::chrono::system_clock::from_time_t(0))//system_clock::now())
    {
        board = std::make_shared<ChessBoard>();

        wPlayer = std::make_shared<Player>(player1, board, true);
        bPlayer = std::make_shared<Player>(player2, board, false);
        setup();
    }

    GameSession() = delete;
    std::shared_ptr<IPlayer> you() {
        if (info.isPlayer) {
            return wPlayer;
        } else {
            return bPlayer;
        }
    }
    virtual std::shared_ptr<IPlayer> enemy() {
        if (info.isPlayer) {
            return bPlayer;
        } else {
            return wPlayer;
        }
    }
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

    GameToken get_token() override { return token_; }
    std::string get_token_string() override { return serializeTimePoint(token_); }

private:
    GInfo info;
    GameToken token_;
};

struct GameSessionComparator {
    bool operator()(const std::shared_ptr<GameSession>& lhs, const std::shared_ptr<GameSession>& rhs) const {
        if (lhs->get_token() < rhs->get_token())
            return true;
        else
            return false;
    }
};

typedef std::map< std::string, std::shared_ptr<GameSession>, StringTokenComparator > GameSessionMap;

#endif //CHESS_GAMESESSION_H

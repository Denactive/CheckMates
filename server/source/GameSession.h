#pragma once

#include <vector>
#include <string>

#include "ChessBoard.h"
#include "ChessPiece.h"
#include "Player.h"
#include "ServerDB.h"
#include "TurnHistory.h"
#include "TurnControl.h"

class IGameSession {
public:
    virtual ~IGameSession() {};
    virtual void CreateLog() = 0;
    virtual void SetBoard() = 0;
    virtual bool MakeMove() = 0;
    virtual std::vector<std::string> all_available_Moves() = 0;
    virtual void DrawHandler() = 0;
    virtual std::string GetStatus() = 0;
    virtual time_t GetTime() = 0;
    virtual void GiveUpHandler() = 0;
    virtual void run() = 0;
    virtual void StalemateHandler() = 0;
};

class GameSession: public IGameSession {
public:
    explicit GameSession(IDBServer* log, ITurnControl* control, IPlayer* player);

    std::vector<std::string> all_available_Moves();
    void SetBoard();
    bool MakeMove();
    void CreateLog();
    void DrawHandler();
    std::string GetStatus();
    void run();
    time_t GetTime();
    void GiveUpHandler();
    void StalemateHandler();
    ~GameSession() = default;

    IDBServer* log;
    ChessBoard board;
    ITurnControl* control;
    IPlayer* wPlayer;
    IPlayer* bPlayer;
    TurnHistory history;
private:
    std::string status;

};


#pragma once

#include <vector>
#include <string>
#include "ChessBoard.h"
#include "ChessPiece.h"
//#include "User.h"
#include "Player.h"
#include "TurnHistory.h"
//#include "Stub.h"
#include "TurnControl.h"
#include "Stats.h"

class iGameSession {
public:
    virtual ~iGameSession() {};
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

class GameSession: public iGameSession {
public:
    GameSession(iTurnControl* control, iPlayer* player);
    std::vector<std::string> all_available_Moves();
    void SetBoard(){};
    bool MakeMove();
    void CreateLog(){};
    void DrawHandler(){};
    std::string GetStatus() {
        return 0;
    };
    void run(){};
    time_t GetTime();

    void GiveUpHandler(){};
    void StalemateHandler(){};
    ~GameSession(){};
 BDServer log;
 ChessBoard board;
iTurnControl* control;
iPlayer* wPlayer;
iPlayer* bPlayer;
private:
    std::string status;
    TurnHistory history;
};


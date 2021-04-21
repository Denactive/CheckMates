#pragma once

#include <vector>
#include <string>
#include "ChessBoard.h"
#include "ChessPiece.h"
#include "Player.h"
#include "User.h"
#include "TurnHistory.h"
#include "Stub.h"
#include "Stats.h"
#include "TurnControl.h"

class iGameSession {
public:
    virtual ~iGameSession() {};
    virtual void CreateLog() = 0;
    virtual void DrawHandler() = 0;
    virtual std::string GetStatus() = 0;
    virtual time_t GetTime() = 0;
    virtual void GiveUpHandler() = 0;
    virtual void run() = 0;
    virtual void StalemateHandler() = 0;

};

class GameSession: public iGameSession {
public:
    GameSession(iTurnControl* l):control(l){};
    iTurnControl* control;
    void CreateLog(){};
    void DrawHandler(){};
    std::string GetStatus() {
        return 0;
    };
    void run(){};
    time_t GetTime() {
        bool turn = control->GetTurn();
        return control->GetTime(turn);
    }
    void GiveUpHandler(){};
    void StalemateHandler(){};
    ~GameSession(){};
private:

   // BDServer log;
   // ChessBoard board;
   // Player wPlayer;
   // Player bPlayer;
    //std::string status;
    //TurnHistory history;

};


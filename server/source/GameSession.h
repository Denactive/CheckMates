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
    virtual void run() = 0;
    virtual std::string GetStatus() = 0;
    virtual void DrawHandler() = 0;
    virtual void GiveUpHandler() = 0;
    virtual void StalemateHandler() = 0;
    virtual void CreateLog() = 0;
    iTurnControl* control;
};

class GameSession: public iGameSession {
public:
    GameSession(iTurnControl* l):control(l){}
    void run();
    std::string GetStatus();
    void DrawHandler();
    void GiveUpHandler();
    void StalemateHandler();
    void CreateLog();
    iTurnControl* control;
private:

   // BDServer log;
   // ChessBoard board;
   // Player wPlayer;
   // Player bPlayer;
    //std::string status;
    //TurnHistory history;

};


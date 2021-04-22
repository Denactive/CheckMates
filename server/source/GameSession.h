#pragma once

#include <vector>
#include <string>
#include "ChessBoard.h"
#include "ChessPiece.h"
//#include "User.h"
#include "Player.h"
#include "TurnHistory.h"
//#include "Stub.h"
//#include "Stats.h"
#include "TurnControl.h"

class iGameSession {
public:
    virtual ~iGameSession() {};
    virtual void CreateLog() = 0;
    virtual void SetBoard() = 0;
    virtual void MakeMove() = 0;
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
    GameSession(iTurnControl* l):control(l){};
    std::vector<std::string> all_available_Moves(){
        std::vector<std::string> vec;
        vec.push_back("new");
        return vec;
    };
    void SetBoard(){};
    void MakeMove(){};
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
private:
    iTurnControl* control;
   // BDServer log;
   // ChessBoard board;
   // Player wPlayer;
   // Player bPlayer;
    //std::string status;
    //TurnHistory history;

};


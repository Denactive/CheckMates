#include "GameSession.h"

GameSession::GameSession(iBDServer* log, iTurnControl* control, iPlayer* player):log(log), control(control), wPlayer(player),bPlayer(player){};
std::vector<std::string> GameSession::all_available_Moves(){
    std::vector<std::string> vec;
    vec.push_back("new");
    return vec;
};

time_t GameSession::GetTime() {
    return control->GetTime(control->GetTurn());
}

bool GameSession::MakeMove() {
    iPlayer* player = NULL;
    if (control->GetTurn()) {
        player = wPlayer;
    } else {
        player = bPlayer;
    }
    return player->try_move();
}
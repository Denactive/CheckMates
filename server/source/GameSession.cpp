#include "GameSession.h"

GameSession::GameSession(iTurnControl* l):control(l){};
std::vector<std::string> GameSession::all_available_Moves(){
    std::vector<std::string> vec;
    vec.push_back("new");
    return vec;
};

time_t GameSession::GetTime() {
    bool turn = control->GetTurn();
    return control->GetTime(turn);
}
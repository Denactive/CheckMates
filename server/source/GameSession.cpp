#include "GameSession.h"

GameSession::GameSession(IDBServer* log, ITurnControl* control, IPlayer* player):log(log), control(control), wPlayer(player),bPlayer(player) {
    std::cout << "game cc-tor\n";
};

std::vector<std::string> GameSession::all_available_Moves() {
    std::vector<std::string> vec;
    vec.push_back("new");
    return vec;
};

std::vector<std::string> all_available_Moves() {
    std::vector<std::string> res;
    return res;
}

time_t GameSession::GetTime() {
    return control->GetTime(control->GetTurn());
}

bool GameSession::MakeMove() {
    IPlayer* player = NULL;
    if (control->GetTurn()) {
        player = wPlayer;
    } else {
        player = bPlayer;
    }
    return player->try_move();
}

void GameSession::SetBoard() { std::cout << "set board\n"; };
void GameSession::CreateLog() { std::cout << "crt log\n"; };
void GameSession::DrawHandler() { std::cout << "draw handler\n"; };
std::string GameSession::GetStatus() {
    return "smtg";
};
void GameSession::run() { std::cout << "game run\n"; };

void GameSession::GiveUpHandler() { std::cout << "gu handler\n"; };
void GameSession::StalemateHandler() { std::cout << "stmt handler\n"; };
#include "GameSession.h"


time_t GameSession::GetTime() {
    bool turn = control->GetTurn();
    return control->GetTime(turn);
}
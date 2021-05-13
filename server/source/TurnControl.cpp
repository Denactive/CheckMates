#include "TurnControl.h"


    void TurnControl::SwitchTurn() { Turn = ~Turn;};
    void TurnControl::EnableTimer() {};
    void TurnControl::StopTimer() {};
    TurnControl::~TurnControl() {};
    time_t TurnControl::GetTime(const bool Turn) {
        return Timer1;
    }
    bool TurnControl::GetTurn(void) {
        return Turn;
};
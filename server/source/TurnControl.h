//
// Created by yura11011 on 15.04.2021.
//

#ifndef CHECKMATES_TURNCONTROL_H
#define CHECKMATES_TURNCONTROL_H
#include "GameSession.h"

class TurnControl {
private:
    void switch_turn();
    void enable_timer();
    void stop_timer();
public:
    time_t Timer1;
    time_t Timer2;
};


#endif //CHECKMATES_TURNCONTROL_H

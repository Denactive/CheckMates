//
// Created by yura11011 on 15.04.2021.
//

#ifndef CHECKMATES_TURNCONTROL_H
#define CHECKMATES_TURNCONTROL_H
#include "GameSession.h"

class iTurnControl {
private:
    virtual void SwitchTurn() = 0;
    virtual void StopTimer() = 0;
    virtual void EnableTimer() = 0;
public:
    virtual ~iTurnControl() { };
    virtual time_t GetTime(bool Turn) = 0;
    virtual bool GetTurn(void) = 0;

};

class TurnControl: public iTurnControl {
private:
    bool Turn;
    time_t Timer1;
    time_t Timer2;
    void SwitchTurn();
    void EnableTimer();
    void StopTimer();
public:
    ~TurnControl();
    time_t GetTime(const bool Turn);
    bool GetTurn(void);
};

#endif //CHECKMATES_TURNCONTROL_H

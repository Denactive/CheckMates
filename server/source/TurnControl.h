#ifndef CHESS_TURNCONTROL_H
#define CHESS_TURNCONTROL_H
#include <ctime>
class ITurnControl {
private:
    virtual void SwitchTurn() = 0;
    virtual void StopTimer() = 0;
    virtual void EnableTimer() = 0;
public:
    virtual ~ITurnControl() { };
    virtual time_t GetTime(bool Turn) = 0;
    virtual bool GetTurn(void) = 0;

};

class TurnControl: public ITurnControl {
private:
    bool Turn;
    time_t Timer1;
    time_t Timer2;
public:
    void SwitchTurn();
    void EnableTimer();
    void StopTimer();
    ~TurnControl();
    time_t GetTime(const bool Turn);
    bool GetTurn(void);
};

#endif //CHESS_TURNCONTROL_H

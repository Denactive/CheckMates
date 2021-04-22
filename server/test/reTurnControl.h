class reTurnControl: public iTurnControl {
public:
    MOCK_METHOD(void, StopTimer, ());
    MOCK_METHOD(void, EnableTimer, ());
    MOCK_METHOD(void, SwitchTurn, ());
    MOCK_METHOD(time_t, GetTime, (bool Turn));
    MOCK_METHOD(bool, GetTurn, ());
};
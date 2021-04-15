#include "GameSession.h"


class iGameSession {
public:
    void run();
    std::string get_status();
    int get_time();
    void draw_handler();
    void give_up_handler();
    void stalemate_handler();
    void create_log();
};

class GameSession: public iGameSession {
public:
    void run();
    std::string get_status();
    int get_time();
    void draw_handler();
    void give_up_handler();
    void stalemate_handler();
    void create_log();
private:
    ChessBoard board;
    Player wPlayer;
    Player bPlayer;
    std::string status;
    TurnControl control;
    TurnHistory history;

};
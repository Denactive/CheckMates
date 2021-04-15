#include "GameSession.h"
#include "ChessBoard.h"
#include "Player.h"

#include <vector>
#include <string>

class GameSession {
public:
    void run();
    std::string get_status();
    int get_time();
    void draw_handler();
private:
    ChessBoard board;
    Player wPlayer;
    Player bPlayer;
    std::string status;
    TurnControl control;
    TurnHistory history;
    void give_up_handler();
    void stalemate_handler();
    void create_log();
};

#include "server.h"


int main() {
    // BE CAREFUL WITH FILEPATH


    ChessBoard board;
    board.set_board();
    Player player1(board, true);
    Player player2(board, false);
    TurnControl control;
    GameSession A(control, player1, player2);
    //A.run();

    A.setup();
    GInfo info = A.send_info();
    while (info.isGame) {
        int turn_accepted = A.run_turn();
        info = A.send_info();
    }

    Options opts("SaberLion-Devs", "127.0.0.1", 8000, 8001, "C:/Users/Denactive/source/repos/SaberDevs_CheckMates/server/storage");
    Server s(opts);


    const unsigned short threads_num = 1;
    asio::io_context ioc{ threads_num };

    s.run(ioc);


    return 0;
}

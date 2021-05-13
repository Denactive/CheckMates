
#include "server.h"

std::array<size_t, M> GetTurn() {
    std::array<size_t, M> turn;
    std::cin >> turn[0] >>  turn[1] >> turn[2] >> turn[3];
    return turn;
}

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
    std::array<size_t, M> turn;
    while (info.isGame) {
        turn = GetTurn();
        int turn_accepted = A.run_turn(turn);
        info = A.send_info();
    }

    Options opts("SaberLion-Devs", "127.0.0.1", 8000, 8001, "C:/Users/Denactive/source/repos/SaberDevs_CheckMates/server/storage");
    Server s(opts);


    const unsigned short threads_num = 1;
    asio::io_context ioc{ threads_num };

    s.run(ioc);


    return 0;
}

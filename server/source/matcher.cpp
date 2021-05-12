//
// Created by denactive on 24.04.2021.
//
#include "matcher.h"

GameSession& MatcherQueue::start_game() {
    std::cout << "Matcher: starting a game\n";
    // TODO fill the constructor correctly
//    GameSession gs = new GameSession(iBDServer* log, iTurnControl* control, iPlayer* player);
    ChessBoard board;
    board.set_board();
    Player player1(board, true);
    Player player2(board, false);
    TurnControl control;
GameSession* gs = new GameSession(control, player1, player2);
    return *gs;
}
void MatcherQueue::push_user(IUser* u) {
    std::cout << "Matcher: pushing user " << u->get_id() << ' ' << u->get_nickname() << "\n";
}

void MatcherQueue::pop_user(IUser* u) {
    std::cout << "Matcher: popping user " << u->get_id() << ' ' << u->get_nickname() << "\n";
}

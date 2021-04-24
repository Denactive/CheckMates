//
// Created by denactive on 24.04.2021.
//
#include "matcher.h"

GameSession& Matcher::start_game() override {
    std::cout << "Matcher: starting a game\n";
    GameSession gs = new GameSession();
    return gs;
}
void Matcher::push_user(IUser* u) override {
    std::cout << "Matcher: pushing user " << u->get_id() << ' ' << u->get_nickname << "\n";
}

void Matcher::pop_user(IUser* u) override {
    std::cout << "Matcher: popping user " << u->get_id() << ' ' << u->get_nickname << "\n";
}

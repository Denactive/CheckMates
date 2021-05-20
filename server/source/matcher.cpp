//
// Created by denactive on 24.04.2021.
//
#include "matcher.h"

std::shared_ptr<GameSession> MatcherQueue::start_game(std::shared_ptr<IUser> p1, std::shared_ptr<IUser> p2) {
    auto GetTurn = []() {
        std::array<size_t, M> turn;
        std::cout << "\nenter input\n";
        std::cin >> turn[0] >> turn[1] >> turn[2] >> turn[3];
        return turn;
    };

    std::cout << "Matcher: starting a game\n";
    // TODO fill the constructor correctly
    //    GameSession gs = new GameSession(iBDServer* log, iTurnControl* control, iPlayer* player);
    
    auto game_session = std::make_shared<GameSession>(p1, p2);
    active_games_cnt++;
    game_session->token = active_games_cnt;
    games_.insert(game_session);

    
    std::array<size_t, M> turn;
    GInfo info = game_session->send_info();

    while (info.isGame) {
        // отправляю Свете info
        // принимаю turn | сейчас turn через консоль

        game_session->prepare_turn();
        // собираем информацию о доступных ходах текущего игрока
        // местоположении фигур и т.п.
        // посылаем эту информацию
        info = game_session->send_info();
        // посылаем информацию о статусе игры
        if (!info.isGame) {
            break;
        }

        // выход из цикла, чтобы не вводить следующий ход, если мат
        // типа получаю от светы
        turn = GetTurn();
        // получаем ход - массив из 4 целых size_t.
        // В качестве параметра передается в функцию run_turn;
        int validation = game_session->run_turn(turn);
        // совершаем ход. возвращается 0, если ход принят, 1 - если не принят
        // тогда снова получаем ход и делаем A.run_turn()
        if (!validation) {
            info = game_session->send_info();
            // отправил Свете
            std::cout << "valid move\n";
        }

    }
    return game_session;
}

void MatcherQueue::push_user(std::shared_ptr<IUser> u) {
    std::cout << "Matcher: pushing user " << u->get_id() << ' ' << u->get_nickname() << "\n";
    q_.push(u);

    if (q_.size() == 2) {
        // startgame
        auto p1 = q_.front();
        q_.pop();
        auto p2 = q_.front();
        q_.pop();
        start_game(p1, p2);
    }
}

void MatcherQueue::pop_user(std::shared_ptr<IUser> u) {
    std::cout << "Matcher: popping user " << u->get_id() << ' ' << u->get_nickname() << "\n";
}

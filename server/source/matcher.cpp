//
// Created by denactive on 24.04.2021.
//
#include "matcher.h"

std::shared_ptr<GameSession> MatcherQueue::start_game(std::shared_ptr<IUser> pw, std::shared_ptr<IUser> pb) {
    auto GetTurn = []() {
        std::array<size_t, M> turn;
        std::cout << "\nenter input\n";
        std::cin >> turn[0] >> turn[1] >> turn[2] >> turn[3];
        return turn;
    };

    std::cout << "Matcher: ";
    // TODO fill the constructor correctly
    //    GameSession gs = new GameSession(iBDServer* log, iTurnControl* control, iPlayer* player);
    
    auto game_session = std::make_shared<GameSession>(pw, pb);
    const auto [game, success] = games_->insert({ game_session->get_token_string(), game_session });
    if (success) {
        std::cout << "the game № " + game->first + " added to the Game Map successfully" << std::endl;
    }
    else {
        std::cout << "the game " + game->first + " has not been added to the map | FAIL" << std::endl;
        return nullptr;
    }
    
    /*
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
           // info = game_session->send_info();
            // отправил Свете
            std::cout << "valid move\n";
        }
    }
    */
    return game_session;
}

std::shared_ptr<GameSession> MatcherQueue::push_user(std::shared_ptr<IUser> u) {
    std::cout << "Matcher: pushing user " << u->get_id() << ' ' << u->get_nickname() << "\n";
    q_.push(u);

    if (q_.size() == 2) {
        auto p1 = q_.front();
        q_.pop();
        auto p2 = q_.front();
        q_.pop();

        std::shared_ptr<GameSession> new_game;
        bool is_first_white = std::chrono::system_clock::now().time_since_epoch().count() % 2;
        if (is_first_white)
            new_game = start_game(p1, p2);
        else
            new_game = start_game(p2, p1);
        
        std::cout << "MatcherQueue::push_user | white player is: " << new_game->wPlayer->get_user()->get_token_string() << " (" << new_game->wPlayer->get_user()->get_nickname() << ")\n";
        std::cout << "                        | black player is: " << new_game->bPlayer->get_user()->get_token_string() << " (" << new_game->bPlayer->get_user()->get_nickname() << ")\n";

        return new_game;
    }
    return nullptr;
}

bool MatcherQueue::pop_user(std::shared_ptr<IUser> u) {
    std::cout << "Matcher: popping user " << u->get_id() << ' ' << u->get_nickname() << "\n";
    return true;
}

#include "GameSession.h"

void GameSession::move(std::shared_ptr<IPlayer>& you, std::shared_ptr<IPlayer>& enemy, std::array<size_t, M>& turn) {
    you->move(turn);
    board->move_chess(turn);
    enemy->is_captured(turn);
}

void GameSession::try_move(std::shared_ptr<IPlayer>& you, std::shared_ptr<IPlayer>& enemy) {
    std::array<size_t, M> turn, reverse, capt;
    std::vector<std::array<size_t, M>> moves = you->access();
    if (moves.empty()) {
        return;
    }
    for (size_t i = 0; i < moves.size(); ++i) {
        turn = moves[i];
        you->move(turn);
        board->move_chess(turn);
        size_t num = enemy->try_capture(turn);
        std::array<size_t, K>fake_turn;
        capt[0] = 10;
        capt[1] = 10;
        fake_turn[0] = turn[2];
        fake_turn[1] = turn[3];
        capt[2] = reverse[0] = turn[2];
        capt[3] = reverse[1] = turn[3];
        reverse[2] = turn[0];
        reverse[3] = turn[1];
        enemy->all_available_Moves();
        auto thr = enemy->all_threatens();
        you->KingUpdate(thr);
        if (is_check(you, enemy)) {
            moves.erase(moves.begin() + i);
            --i;
        }
        you->move(reverse);
        board->move_chess(reverse);
        if (num != 2 * N) {
            enemy->move(capt);
            cell Cell = White;
            if (info.isPlayer) {
                Cell = Black;
            }
            board->set(Cell, capt[2], capt[3]);
        }
    }
}


void GameSession::CreateLog() { std::cout << "crt log\n"; };

bool GameSession::GameStatus() {
    return info.isGame;
};

void GameSession::print_moves(std::shared_ptr<IPlayer>& you) {
    std::vector<std::array<size_t, M>> moves = you->access();
    for (auto i = moves.begin(); i < moves.end(); ++i) {
        std::cout << (*i)[0] << ' ' << (*i)[1] << ' ' << (*i)[2] << ' ' << (*i)[3] << '\n';
    }
}


bool GameSession::is_check(std::shared_ptr<IPlayer>& you, std::shared_ptr<IPlayer>& enemy) {
    std::array<size_t, K> p;
    const size_t* pos = you->where();
    p[0] = pos[0];
    p[1] = pos[1];
    std::set<std::array<size_t, K>> thr = enemy->all_threatens();
    auto f = thr.find(p);
    if (f == thr.end()) {
        return false;
    }
    return true;
}

bool GameSession::is_mate(std::shared_ptr<IPlayer>& you, std::shared_ptr<IPlayer>& enemy) {

    std::vector<std::array<size_t, M>> avail = you->access();
    if (is_check(you, enemy) && avail.size() == 0) {
        return true;
    }
    return false;

};
bool GameSession::is_stalemate(std::shared_ptr<IPlayer>& you, std::shared_ptr<IPlayer>& enemy) {
    std::vector<std::array<size_t, M>> avail = you->access();
    if (!is_check(you, enemy) && avail.size() == 0) {
        return true;
    }
    return false;

};

void GameSession::setup() {
    std::cout << "game start\n";
    board->set_board();
    wPlayer->set_pieces();
    bPlayer->set_pieces();
    std::set<std::array<size_t, K>> thr = wPlayer->all_threatens();
    bPlayer->KingUpdate(thr);
    thr = bPlayer->all_threatens();
    wPlayer->KingUpdate(thr);

    info.isGame = true;
    info.isPlayer = false;
    info.isVictory = 0;
    info.isCheck = false;
    info.turn = { 0, 0 , 0 ,0 };
}
int GameSession::prepare_turn() {
    std::set<std::array<size_t, K>> thr;

    info.isPlayer = !info.isPlayer;
    std::shared_ptr<IPlayer> you = bPlayer;
    std::shared_ptr<IPlayer> enemy = wPlayer;
    if (info.isPlayer) {
        you = wPlayer;
        enemy = bPlayer;
    }
    enemy->all_available_Moves();
    thr = enemy->all_threatens();
    you->all_available_Moves();
    you->KingUpdate(thr);
    board->draw_board();
    try_move(you, enemy);
    you->print_pos();
    if (is_check(you, enemy)) {
        info.isCheck = true;
        try_move(you, enemy);
        std::cout << "CHECK!!";
    }

    if (is_stalemate(you, enemy)) {
        info.isGame = false;
        info.isVictory = 0;
        std::cout << "STALEMATE!!";
    }
    if (is_mate(you, enemy)) {
        info.isGame = false;
        info.isVictory = 1;
        if (info.isPlayer) {
            info.isVictory = 2;
        }
        std::cout << "CHECKMATE!!";
        return 0;
    }
    print_moves(you);
    for (auto i = thr.begin(); i != thr.end(); ++i) {
        std::cout << (*i)[0] << ' ' << (*i)[1] << '\n';
    }
    return 0;
}

int GameSession::run_turn(std::array<size_t, M>& turn) {
    bool move_accepted = false;

    std::shared_ptr<IPlayer> you = bPlayer;
    std::shared_ptr<IPlayer> enemy = wPlayer;
    size_t horiz = 7;
    if (info.isPlayer) {
        you = wPlayer;
        horiz = 0;
        enemy = bPlayer;
    }
    std::vector<std::array<size_t, M>> moves = you->access();
    for (auto i = moves.begin(); i != moves.end(); ++i) {
        if (*i == turn) {
            move_accepted = true;
            you->flag_castl(turn);
            std::cout << "true\n";
            break;
        }
    }
    if (move_accepted) {
        move(you, enemy, turn);
        if((turn[0] == 0 || turn[0] == 7) && (turn[1] == 4) && (turn[3] == turn [1] - 2)) {
            turn[1] = 0;
            turn[3] = 3;
            move(you, enemy, turn);
        }
        if((turn[0] == 0 || turn[0] == 7) && (turn[1] == 4) && (turn[3] == turn [1] + 2)) {
            turn[1] = 7;
            turn[3] = 5;
            move(you, enemy, turn);
        }
        info.turn = turn;
        return 0;
    }
    else {
        info.turn = { 0, 0 , 0, 0 };
        return 1;
    }
}

#include "GameSession.h"
#include "iostream"

GameSession::GameSession(ITurnControl& control, IPlayer& player1, IPlayer& player2):
control(control), wPlayer(player1), bPlayer(player2), board(player1.getboard()){};

void GameSession::move(IPlayer* you, IPlayer* enemy, std::array<size_t, M> turn) {
    you->move(turn);
    board.move_chess(turn);
    enemy->is_captured(turn);
}

void GameSession::try_move(IPlayer* you, IPlayer* enemy) {
    std::array<size_t, M> turn, reverse, capt;
    std::vector<std::array<size_t, M>>& moves = you->access();
    auto i = moves.end() - 1;
    while (i >= moves.begin()) {
        turn = *(i);
        //std::cout << turn[0] << turn[1] <<turn [2] << turn [3] <<'\n';
        you->move(turn);
       // std::cout <<you->where()[0] << you->where()[1]<< '\n';
        //King* Kin = dynamic_cast<King *>(you->pieces[4]);
        //std::cout <<Kin->where()[0] <<Kin->where()[1] << '\n';
        board.move_chess(turn);
        size_t num = enemy->try_capture(turn);
        std::array<size_t, K>fake_turn;
        capt[0] = 10;
        capt[1] = 10;
        fake_turn [0] = turn[2];
        fake_turn [1] = turn[3];
        capt[2] =  reverse[0] = turn[2];
        capt[3] =  reverse [1] = turn[3];
        reverse[2] = turn[0];
        reverse [3] = turn[1];

        enemy->all_available_Moves();
        auto thr = enemy->all_threatens();
        you->KingUpdate(thr);
        if (is_check(you, enemy)) {
            moves.erase(i);
            //std::cout << (*i)[0] << (*i)[1] <<(*i)[2] << (*i)[3] <<'\n';
        } else {
            //board.draw_board();
            //std::cout << '\n' <<you->where()[0] << you->where()[1]<< '\n';
        }
        --i;
    you->move(reverse);
    board.move_chess(reverse);
    if (num != 2*N) {
       enemy->move(capt);
       cell Cell = White;
        if (info.isPlayer) {
            Cell = Black;
        }
        board.set(Cell, capt[2], capt[3]);
    }
    }
}

std::array<size_t, M> GameSession::GetTurn() {
    std::array<size_t, M> turn;
    std::cin >> turn[0] >>  turn[1] >> turn[2] >> turn[3];
    return turn;
}

time_t GameSession::GetTime() {
    return control.GetTime(control.GetTurn());
}

bool GameSession::MakeMove() {

    return true;
}

void GameSession::SetBoard() { std::cout << "set board\n"; };
void GameSession::CreateLog() { std::cout << "crt log\n"; };
void GameSession::DrawHandler() { std::cout << "draw handler\n"; };
bool GameSession::GameStatus() {
    return info.isGame;
};

void GameSession::print_moves(IPlayer* you) {
    std::vector<std::array<size_t, M>> moves = you->access();
    for (auto i = moves.begin(); i < moves.end(); ++i) {
        std::cout << (*i)[0] << ' '<< (*i)[1] << ' '<< (*i)[2] << ' '<< (*i)[3] << '\n';
        }
}


void GameSession::run() {
    std::cout << "game run\n";
    board.set_board();
    std::array<std::array<cell, N>, N> bd =  board.get_board();

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << bd[i][j] << ' ';
        }
        std::cout << '\n';
    }
    wPlayer.set_pieces();
    bPlayer.set_pieces();
    std::set<std::array<size_t, K>> thr = wPlayer.all_threatens();
    bPlayer.KingUpdate(thr);
    thr = bPlayer.all_threatens();
    wPlayer.KingUpdate(thr);
    struct GInfo{
        bool isPlayer;
        bool isGame;
        char isVictory;
        bool isCheck;
    };

    info.isGame = true;
    info.isPlayer = false;
    info.isVictory = 0;
    info.isCheck = false;


    while(info.isGame) {
        info.isPlayer = !info.isPlayer;
        IPlayer* you = &bPlayer;
        IPlayer* enemy = &wPlayer;
        if (info.isPlayer) {
            you = &wPlayer;
            enemy = &bPlayer;
        }
        enemy->all_available_Moves();
        thr = enemy->all_threatens();
        you->all_available_Moves();
        you->KingUpdate(thr);

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
            break;
        }
        print_moves(you);
        for (auto i = thr.begin(); i != thr.end(); ++i) {
            std::cout << (*i)[0] << ' '<< (*i)[1]  << '\n';
        }
        bool move_accepted = false;
        std::cout << "\nenter input\n";
        std::array<size_t, M> turn;
        while (!move_accepted) {
        turn = GetTurn ();
        std::vector<std::array<size_t, M>> moves = you->access();
        for (auto i = moves.begin(); i != moves.end(); ++i) {
             if (*i == turn) {
                 move_accepted = true;
                 std::cout << "true\n";
                 break;
             }
        }
        }
      //  auto pos = you->pieces[3]->where();
        //std::cout  <<"\n %"<< pos[0] <<pos[1]<<"\n %";
        move(you, enemy, turn);

        board.draw_board();
        //std::cout <<"\n~~~ \n";
         //you->print_pos();
        //enemy->print_pos();
       // std::cout <<"\n~~~ \n";
    }

}

bool GameSession::is_check(IPlayer* you, IPlayer* enemy) {
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

bool GameSession::is_mate(IPlayer* you, IPlayer* enemy) {

    std::vector<std::array<size_t, M>> avail = you->access();
    if (is_check(you, enemy) && avail.size() == 0)  {
        return true;
    }
    return false;

};
bool GameSession::is_stalemate(IPlayer* you, IPlayer* enemy){
    std::vector<std::array<size_t, M>> avail = you->access();
    if (!is_check(you, enemy) && avail.size() == 0)  {
        return true;
    }
    return false;

};

void GameSession::GiveUpHandler() { std::cout << "gu handler\n"; };
void GameSession::StalemateHandler() { std::cout << "stmt handler\n"; };
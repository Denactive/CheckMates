#include "Chesspiece.h"
#include "iostream"

King::King(size_t i,size_t j, std::shared_ptr<ChessBoard> board):
    board(board) {
    castle = true;
    leftrook = true;
    rightrook = true;
    position[0] = i;
    position[1] = j;
};

void King::Update_King(std::set<std::array<size_t, K>> input) {
    enemy_threats.clear();
    enemy_threats = input;
}


void King::castling() {
   // std::cout <<"\n^^" <<castle <<leftrook <<rightrook;
    if(castle && leftrook) {
        std::array<size_t, M> king;
        size_t i = position[0];
        size_t j = position[1];
        std::array<size_t, K> check, tries, cast;
        king[0] = check[0] = i;
        king[1] = check[1] = j;
        tries[0] = i;
        tries[1] = j - 1;
        king[2] = cast [0] = i;
        king[3] = cast [1] = j - 2;

        auto bd = board->get_board();
        if (bd[i][1] == Empty && bd[i][2] == Empty && bd[i][3] == Empty) {
            if (threat.find(check) == threat.end() && threat.find(tries) == threat.end()
                && threat.find(cast) == threat.end()) {
                avail_moves.push_back(king);
            }
        }
    }
    if(castle && rightrook) {
        std::array<size_t, M> king;
        size_t i = position[0];
        size_t j = position[1];
        std::array<size_t, K> check, tries, cast;
        king[0] = check[0] = i;
        king[1] = check[1] = j;
        tries[0] = i;
        tries[1] = j + 1;
        king[2] = cast [0] = i;
        king[3] = cast [1] = j + 2;

        auto bd = board->get_board();
        if (bd[i][5] == Empty && bd[i][6] == Empty) {
            if (threat.find(check) == threat.end() && threat.find(tries) == threat.end()
                && threat.find(cast) == threat.end()) {
                avail_moves.push_back(king);
            }
        }
    }

    }


std::vector<std::array<size_t, M>> King::available_moves() {
    avail_moves.clear();
    size_t i = position[0];
    size_t j = position[1];
    std::array<size_t, M> mov;
    std::array<size_t, K> tries;
    mov[0] = i;
    mov[1] = j;
    auto bd = board->get_board();
    cell temp = bd[i][j];
    for (size_t k = (i > 0) ? i - 1 : i; k <= i + 1 && k < 8; ++k) {
        for (size_t m = (j > 0) ? j - 1 : j; m <= j + 1 && m < 8; ++m) {
            if (!(k == i && m == j)) {
                if (bd[k][m] != temp) {
                    mov[2] = k;
                    tries[0] = k;
                    mov[3] = m;
                    tries[1] = m;
                    if (threat.find(tries) == threat.end()) {
                        avail_moves.push_back(mov);
                    }
                }
            }
        }
    }
    castling();
    return avail_moves;
}
std::set<std::array<size_t, K>> King::threatens() {
    threat.clear();
    size_t i = position[0];
    size_t j = position[1];
    std::array<size_t, K> mov;
    auto bd = board->get_board();
    cell temp = bd[i][j];
    for (size_t k = (i > 0) ? i - 1 : i; (k <= i + 1) && (k < 8); k++) {
        for (size_t m = (j > 0) ? j - 1 : j; (m <= j + 1) && (m < 8); m++) {
            if (!(k == i && m == j)) {
                if (bd[k][m] != temp) {
                    mov[0] = k;
                    mov[1] = m;
                    threat.insert(mov);
                }
            }
        }
    }
    return threat;
}

King::~King() {

}

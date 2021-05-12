#include "Chesspiece.h"
#include "iostream"

King::King(size_t i,size_t j, ChessBoard& board): board(board) {
    position[0] = i;
    position[1] = j;
};

void King::Update_King(std::set<std::array<size_t, K>> input) {
    enemy_threats.clear();
    enemy_threats = input;
}


void King::castling() {

}


std::vector<std::array<size_t, M>> King::available_moves() {
    avail_moves.clear();
    size_t i = position[0];
    size_t j = position[1];
    std::array<size_t, M> mov;
    std::array<size_t, K> tries;
    mov[0] = i;
    mov[1] = j;
    auto bd = board.get_board();
    cell temp = bd[i][j];
    for (size_t k = (i > 0) ? i - 1 : i; k <= i + 1 && k < 8; ++k) {
        for (size_t m = (j > 0) ? j - 1 : j; m <= j + 1 && m < 8; ++m) {
            if (!(k == i && m == j)) {
                if (bd[k][m] != temp) {
                    mov[2]  = k;
                    tries[0] = k;
                    mov[3]  = m;
                    tries[1] = m;
                    if(threat.find(tries) == threat.end()) {
                        avail_moves.push_back(mov);
                    }
                }
            }
        }
    }
    return avail_moves;
}
std::set<std::array<size_t, K>> King::threatens() {
    threat.clear();
    size_t i = position[0];
    size_t j = position[1];
    std::array<size_t, K> mov;
    auto bd = board.get_board();
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

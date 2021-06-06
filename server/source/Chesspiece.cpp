#include "Chesspiece.h"
#include <iostream>
#include "bishop.h"
#include "rook.h"

std::vector<std::array<size_t, M>> Queen::available_moves() {
    avail_moves.clear();
    size_t i = position[0];
    size_t j = position[1];
    std::array<size_t, M> mov;
    mov[0] = i;
    mov[1] = j;
    auto bd = board->get_board();
    if (i > 7 || j > 7) {
        return avail_moves;
    }
    bishop (i, j, mov, avail_moves, bd);
    rook (i,  j,  mov,  avail_moves, bd);
    return avail_moves;
}
std::set<std::array<size_t, K>> Queen::threatens() {
    threat.clear();
    std::array<size_t, K> mov;
    for (auto i = avail_moves.begin(); i != avail_moves.end(); ++i) {
        mov[0] = (*i)[2];
        mov[1] = (*i)[3];
        threat.insert(mov);
    }
    return threat;
}




std::vector<std::array<size_t, M>> Rook::available_moves() {
    avail_moves.clear();
    size_t i = position[0];
    size_t j = position[1];
    std::array<size_t, M> mov;
    mov[0] = i;
    mov[1] = j;
    auto bd = board->get_board();
    if (i > 7 || j > 7) {
        return avail_moves;
    }
    rook (i,  j,  mov,  avail_moves, bd);
    return avail_moves;
}

std::set<std::array<size_t, K>> Rook::threatens() {
    threat.clear();
    std::array<size_t, K> mov;
    for (auto i = avail_moves.begin(); i != avail_moves.end(); ++i) {
        mov[0] = (*i)[2];
        mov[1] = (*i)[3];
        threat.insert(mov);
    }
    return threat;
}


std::vector<std::array<size_t, M>> Knight::available_moves() {
    avail_moves.clear();
    size_t i = position[0];
    size_t j = position[1];
    std::array<size_t, M> mov;
    mov[0] = i;
    mov[1] = j;
    auto bd = board->get_board();
    if (i > 7 || j > 7) {
        return avail_moves;
    }
    cell temp = bd[i][j];
    size_t k = 0;
    size_t m = 0;
    if ((k = i + 1) < 8) {
        if((m = j + 2) < 8) {
            if (bd[k][m] != temp) {
                mov[2] = k;
                mov[3] = m;
                avail_moves.push_back(mov);
            }
        }
        if((m = j - 2) < 8) {
            if (bd[k][m] != temp) {
                mov[2] = k;
                mov[3] = m;
                avail_moves.push_back(mov);
            }
        }
    }

    if ((k = i - 1) < 8) {
        if((m = j + 2) < 8) {
            if (bd[k][m] != temp) {
                mov[2] = k;
                mov[3] = m;
                avail_moves.push_back(mov);
            }
        }
        if((m = j - 2) < 8) {
            if (bd[k][m] != temp) {
                mov[2] = k;
                mov[3] = m;
                avail_moves.push_back(mov);
            }
        }
    }

    if ((k = i + 2) < 8) {
        if((m = j + 1) < 8) {
            if (bd[k][m] != temp) {
                mov[2] = k;
                mov[3] = m;
                avail_moves.push_back(mov);
            }
        }
        if((m = j - 1) < 8) {
            if (bd[k][m] != temp) {
                mov[2] = k;
                mov[3] = m;
                avail_moves.push_back(mov);
            }
        }
    }

    if ((k = i - 2) < 8) {
        if((m = j + 1) < 8) {
            if (bd[k][m] != temp) {
                mov[2] = k;
                mov[3] = m;
                avail_moves.push_back(mov);
            }
        }
        if((m = j - 1) < 8) {
            if (bd[k][m] != temp) {
                mov[2] = k;
                mov[3] = m;
                avail_moves.push_back(mov);
            }
        }
    }
    return avail_moves;
}

std::set<std::array<size_t, K>> Knight::threatens() {
    threat.clear();
    std::array<size_t, K> mov;
    for (auto i = avail_moves.begin(); i < avail_moves.end(); ++i) {
        mov[0] = (*i)[2];
        mov[1] = (*i)[3];
        threat.insert(mov);
    }
    return threat;
}


std::vector<std::array<size_t, M>> Bishop::available_moves() {
    avail_moves.clear();
    size_t i = position[0];
    size_t j = position[1];
    std::array<size_t, M> mov;
    mov[0] = i;
    mov[1] = j;
    auto bd = board->get_board();
    if (i > 7 || j > 7) {
        return avail_moves;
    }
    cell temp = bd[i][j];
    bishop (i, j, mov, avail_moves, bd);
    return avail_moves;
}
std::set<std::array<size_t, K>> Bishop::threatens() {
    threat.clear();
    std::array<size_t, K> mov;
    for (auto i = avail_moves.begin(); i < avail_moves.end(); ++i) {
        mov[0] = (*i)[2];
        mov[1] = (*i)[3];
        threat.insert(mov);
    }
    return threat;
}


std::vector<std::array<size_t, M>> Pawn::available_moves() {
    avail_moves.clear();
    size_t i = position[0];
    size_t j = position[1];
    std::array<size_t, M> mov;
    mov[0] = i;
    mov[1] = j;
    auto bd = board->get_board();
    if (i > 7 || j > 7) {
        return avail_moves;
    }
    cell temp = bd[i][j];
    if (white) {
        if ((i == 1) && (bd[i + 2][j] == Empty)) {
            mov[2] = i + 2;
            mov[3] = j;
            avail_moves.push_back(mov);
        }
        if ((i + 1 < 8) && (bd[i + 1][j] == Empty)) {
            mov[2] = i + 1;
            mov[3] = j;
            avail_moves.push_back(mov);
        }
        if ((i + 1 < 8) && (j - 1 < 8) && (bd[i + 1][j - 1] != temp) && (bd[i + 1][j - 1] != Empty)) {
            mov[2] = i + 1;
            mov[3] = j - 1;
            avail_moves.push_back(mov);
        }
        if ((i + 1 < 8) && (j + 1 < 8) && (bd[i + 1][j + 1] != temp) && (bd[i + 1][j + 1] != Empty)) {
            mov[2] = i + 1;
            mov[3] = j + 1;
            avail_moves.push_back(mov);
        }

    } else {
        if ((i == 6) && (bd[i - 2][j] == Empty)) {
            mov[2] = i - 2;
            mov[3] = j;
            avail_moves.push_back(mov);
        }
        if ((i - 1 < 8)  && (bd[i - 1][j] == Empty)) {
            mov[2] = i - 1;
            mov[3] = j;
            avail_moves.push_back(mov);
        }
        if ((i - 1 < 8) && (j - 1 < 8) && (bd[i - 1][j - 1] != temp) && (bd[i - 1][j - 1] != Empty)) {
            mov[2] = i - 1;
            mov[3] = j - 1;
            avail_moves.push_back(mov);
        }
        if ((i - 1 < 8) && (j + 1 < 8) && (bd[i - 1][j + 1] != temp) && (bd[i - 1][j + 1] != Empty)) {
            mov[2] = i - 1;
            mov[3] = j + 1;
            avail_moves.push_back(mov);
        }

    }
    return avail_moves;
}

std::set<std::array<size_t, K>> Pawn::threatens() {
    threat.clear();
    size_t i = position[0];
    size_t j = position[1];
    std::array<size_t, K> mov;
    auto bd = board->get_board();
    if (white) {
        if ((i + 1 < 8) && (j - 1 < 8)) {
            mov[0] = i + 1;
            mov[1] = j - 1;
            threat.insert(mov);
        }
        if ((i + 1 < 8) && (j + 1 < 8)) {
            mov[0] = i + 1;
            mov[1] = j + 1;
            threat.insert(mov);
        }

    } else {
        if ((i - 1 < 8) && (j - 1 < 8)) {
            mov[0] = i - 1;
            mov[1] = j - 1;
            threat.insert(mov);
        }
        if ((i - 1 < 8) && (j + 1 < 8)) {
            mov[0] = i - 1;
            mov[1] = j + 1;
            threat.insert(mov);
        }

}
    return threat;
}


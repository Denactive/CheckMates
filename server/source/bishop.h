#include "Chesspiece.h"

void bishop (size_t i, size_t j, std::array<size_t, M>& mov, std::vector<std::array<size_t, M>>& avail_moves, std::array<std::array<cell, N>, N>& bd) {
    cell temp = bd[i][j];
    for (size_t k = i + 1, m = j + 1; (k < 8) && (m < 8); ++k, ++m) {
        if (bd[k][m] == Empty) {
            mov[2] = k;
            mov[3] = m;
            avail_moves.push_back(mov);
        } else {
            if (bd[k][m] != temp) {
                mov[2] = k;
                mov[3] = m;
                avail_moves.push_back(mov);
            }
            break;
        }
    }

    for (size_t k = i - 1, m = j - 1; (k < 8) && (m < 8); --k, --m) {
        if (bd[k][m] == Empty) {
            mov[2] = k;
            mov[3] = m;
            avail_moves.push_back(mov);
        } else {
            if (bd[k][m] != temp) {
                mov[2] = k;
                mov[3] = m;
                avail_moves.push_back(mov);
            }
            break;
        }
    }

    for (size_t k = i + 1, m = j - 1; (k < 8) && (m < 8); ++k, --m) {
        if (bd[k][m] == Empty) {
            mov[2] = k;
            mov[3] = m;
            avail_moves.push_back(mov);
        } else {
            if (bd[k][m] != temp) {
                mov[2] = k;
                mov[3] = m;
                avail_moves.push_back(mov);
            }
            break;
        }
    }

    for (size_t k = i - 1, m = j + 1; (k < 8) && (m < 8); --k, ++m) {
        if (bd[k][m] == Empty) {
            mov[2] = k;
            mov[3] = m;
            avail_moves.push_back(mov);
        } else {
            if (bd[k][m] != temp) {
                mov[2] = k;
                mov[3] = m;
                avail_moves.push_back(mov);
            }
            break;
        }
    }
}
#include "Player.h"


std::vector<std::array<size_t, M>>  Player::all_available_Moves() {
    moves.clear();
    for (int i = 0; i < 2 * N; ++i) {
        auto v1 = pieces[i]->available_moves();
        moves.reserve(v1.size() + moves.size());
        moves.insert(moves.end(), v1.begin(), v1.end());
    }
    return moves;
};

void Player::print_pos() {
    for (int i = 0; i < 2 * N; ++i) {
        auto p = pieces[i]->where();
        std::cout  <<"^"<< p[0] << p[1] <<'\n';
    }
}

std::set<std::array<size_t, K>>  Player::all_threatens() {
    threats.clear();
    for (int i = 0; i < 2 * N; ++i) {
        auto v1 = pieces[i]->threatens();
        threats.insert(v1.begin(), v1.end());
    }
    return threats;
};



void Player::set_pieces() {
    size_t i = 7;
    if (wb) {
        i = 0;
    }

    pieces[0] = new Rook(i, 0, board);
    pieces[1] = new Knight(i, 1, board);
    pieces[2] = new Bishop(i, 2, board);
    pieces[3] = new Queen(i, 3, board);;
    pieces[4] = new King(i, 4, board);;
    pieces[5] = new Bishop(i, 5, board);
    pieces[6] = new Knight(i, 6, board);
    pieces[7] = new Rook(i, 7, board);

    i = 6;
    if (wb) {
        i = 1;
    }

    for (size_t j = 0; j < N; ++j) {
        pieces[8 + j] = new Pawn (i, j, board);
    }

}


void Player::move(std::array<size_t, M> turn) {
    size_t num = 0;
    if (turn[0] == where()[0] && turn[1] == where()[1]) {
        king->move(turn);
    }
    for (int i = 0; i < 2 * N; ++i) {
        auto a = pieces[i]->where();
        if (turn[0] == a[0] && turn[1] == a[1]) {
            num = i;
            break;
        }
    }
        if (num != 2 * N) {

            pieces[num]->move(turn);
        }

}
void Player::is_captured(std::array<size_t, M> turn) {
    size_t num = 2 * N;
    for (int i = 0; i < 2 * N; ++i) {
        auto a = pieces[i]->where();
        if (turn[2] == a[0] && turn[3] == a[1]) {
            num = i;
            break;
        }
    }
    if (num != 2 * N) {
        pieces[num]->is_captured();
    }
}
    size_t Player::try_capture(std::array<size_t, M> turn) {
        size_t num = 2 * N;
        for (int i = 0; i < 2 * N; ++i) {
            auto a = pieces[i]->where();
            if (turn[2] == a[0] && turn[3] == a[1]) {
                num = i;
                break;
            }
        }
        if (num != 2 * N) {
            pieces[num]->try_capture();
        }
        return num;

    }




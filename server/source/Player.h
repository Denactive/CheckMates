#ifndef CHECKMATES_PLAYER_H
#define CHECKMATES_PLAYER_H


class Player {
private:
    ChessBoard& board:
             - user: &User

    - chess_piece[16]

    +

    + all_available_Moves(): std::array<std::string>

    + try_move()
    + is_check()
    + is_mate()
    + is_statemate()+ get_user(): User

    + set_pieces

};


#endif //CHECKMATES_PLAYER_H

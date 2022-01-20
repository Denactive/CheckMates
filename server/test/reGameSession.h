//
// Created by denactive on 25.04.2021.
//

#ifndef SERVER_REGAMESESSION_H
#define SERVER_REGAMESESSION_H

#include <array>
#include "../source/GameSession.h"

class reGameSession: public IGameSession {
public:
    MOCK_METHOD(void, CreateLog, (), (override));
    MOCK_METHOD(bool, GameStatus, (), (override));
    MOCK_METHOD(int, run_turn, ((std::array<size_t, M>&)), (override));
    MOCK_METHOD(std::shared_ptr<IPlayer>, you, (int), (override));
    MOCK_METHOD(std::shared_ptr<IPlayer>, enemy, (int), (override));
    MOCK_METHOD(bool, is_check, (std::shared_ptr<IPlayer>&, std::shared_ptr<IPlayer>&), (override));
    MOCK_METHOD(bool, is_mate, (std::shared_ptr<IPlayer>&, std::shared_ptr<IPlayer>&), (override));
    MOCK_METHOD(bool, is_stalemate, (std::shared_ptr<IPlayer>& you, std::shared_ptr<IPlayer>& enemy), (override));
    MOCK_METHOD(GInfo, send_info, (), (override));
    MOCK_METHOD(int, prepare_turn, (), (override));
    MOCK_METHOD(GameToken, get_token, (), (override));
    MOCK_METHOD(std::string, get_token_string, (), (override));
    MOCK_METHOD(bool, is_in_game, (std::shared_ptr<IPlayer>&), (override));
    MOCK_METHOD(void, print_moves, (std::shared_ptr<IPlayer>& you), (override));
};
#endif //SERVER_REGAMESESSION_H

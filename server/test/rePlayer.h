#include "Player.h"

class rePlayer: public IPlayer {
public:
    MOCK_METHOD(std::shared_ptr<WebSocketSession>, get_session, (), (override));
    MOCK_METHOD(void, set_session, (std::shared_ptr<WebSocketSession>), (override));
    MOCK_METHOD((std::vector<std::array<size_t, M>>),  all_available_Moves, (), (override));
    MOCK_METHOD(void, move, ((std::array<size_t, M>)), (override));
    MOCK_METHOD(void, is_captured, ((std::array<size_t, M>)), (override));
    MOCK_METHOD(size_t, try_capture, ((std::array<size_t, M> turn)), (override));
    MOCK_METHOD(std::shared_ptr<IUser>, get_user, (), (override));
    MOCK_METHOD(void, set_pieces, (), (override));
    MOCK_METHOD(void, flag_castl, ((std::array<size_t, M>)), (override));
    MOCK_METHOD(void, print_pos, (), (override));
    MOCK_METHOD(std::shared_ptr<ChessBoard>, getboard, (), (override));
    MOCK_METHOD(void, KingUpdate, ((std::set<std::array<size_t, K>>)), (override));
    MOCK_METHOD(const size_t*, where, (), (override));
    MOCK_METHOD((std::vector<std::array<size_t, M>>&),  access, (), (override));
    MOCK_METHOD((std::set<std::array<size_t, K>>), all_threatens, (), (override));
};

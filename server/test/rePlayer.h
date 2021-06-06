#include <array>
#include <cstddef>
#include <memory>
#include <vector>


/*virtual std::shared_ptr<WebSocketSession> get_session() = 0;
virtual void set_session(std::shared_ptr<WebSocketSession>) = 0;
virtual std::vector<std::array<size_t, M>>  all_available_Moves() = 0;
virtual void move(std::array<size_t, M> turn) = 0;
virtual void is_captured(std::array<size_t, M> turn) = 0;
virtual size_t try_capture(std::array<size_t, M> turn) = 0;
virtual std::shared_ptr<IUser> get_user() = 0;
virtual void set_pieces() = 0;
virtual void flag_castl(std::array<size_t, M> turn) = 0;
virtual void print_pos() = 0;
virtual std::shared_ptr<ChessBoard> getboard () = 0;
virtual void KingUpdate(std::set<std::array<size_t, K>> thr) = 0;
virtual const size_t* where() = 0;
virtual std::vector<std::array<size_t, M>>& access() = 0;
virtual std::set<std::array<size_t, K>> all_threatens() = 0;
 */
class rePlayer: public IPlayer {
public:
    MOCK_METHOD((std::vector<std::array<size_t, 4>>), all_available_Moves, (), (override));
    MOCK_METHOD(void, set_session, (std::shared_ptr<WebSocketSession>), (override));
    MOCK_METHOD((void), move, (std::array<size_t, 4>), (override));
    MOCK_METHOD(std::shared_ptr<WebSocketSession>, get_session, (), (override));
};

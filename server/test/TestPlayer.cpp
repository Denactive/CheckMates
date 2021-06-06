#include <boost/asio/ip/tcp.hpp>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "GameSession.h"
#include "rePlayer.h"

using ::testing::Return;
using ::testing::AtLeast;
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
virtual std::set<std::array<size_t, K>> all_threatens() = 0;virtual std::shared_ptr<WebSocketSession> get_session() = 0;
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
virtual std::set<std::array<size_t, K>> all_threatens() = 0; */


TEST(Player, Mock) {
    rePlayer player;

    //auto session = std::make_shared<WebSocketSession()>;
   // ON_CALL(player, get_session())
           // .WillByDefault(Return(session));
    std::array<size_t, 4> turn = {0, 0, 1, 1};
    std::vector<std::array<size_t, 4>> vec;
    vec.push_back(turn);
    ON_CALL(player, all_available_Moves())
            .WillByDefault(Return(vec));
    EXPECT_EQ(player.all_available_Moves(), vec);
    size_t pos = 1;
    ON_CALL(player, try_capture((std::array<size_t, M>) turn))
    .WillByDefault(Return(pos));
    EXPECT_EQ(player.try_capture(turn), pos);
    
   /* ON_CALL(player, try_move())
            .WillByDefault(Return(true));
    ON_CALL(player, is_check())
            .WillByDefault(Return(false));
    ON_CALL(player, is_mate())
            .WillByDefault(Return(false));
    ON_CALL(player, is_stalemate())
            .WillByDefault(Return(false));
    ON_CALL(player, GetUserId())
            .WillByDefault(Return(0));



*/
}



#include <boost/asio/ip/tcp.hpp>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "GameSession.h"
#include "rePlayer.h"

using ::testing::Return;
using ::testing::AtLeast;


TEST(Player, Mock) {
    rePlayer player;
    ON_CALL(player, get_session())
            .WillByDefault(Return(nullptr));
    EXPECT_FALSE(player.get_session());
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
    std::shared_ptr<IUser> iUser = nullptr;
    ON_CALL(player,  get_user())
            .WillByDefault(Return(nullptr));
    EXPECT_FALSE(player.get_user());
    ChessBoard board;
    std::shared_ptr<ChessBoard> bd = std::make_shared<ChessBoard>(board);
    ON_CALL(player, getboard())
            .WillByDefault(Return(bd));
    EXPECT_EQ(player.getboard(), bd);
    ON_CALL(player, where())
            .WillByDefault(Return(&pos));
    EXPECT_EQ(player.where(), &pos);

    /*ON_CALL(player, access())
            .WillByDefault(Return(vec)); // limitations of GMock
            */
    std::set<std::array<size_t, 2>> threat;
    std::array<size_t, 2> to = {1, 2};
    threat.insert(to);
    EXPECT_CALL(player, all_threatens).Times(AtLeast(1)).WillOnce(Return(threat));
    EXPECT_EQ(to, player.all_threatens());

}



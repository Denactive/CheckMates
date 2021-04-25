#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "net.h"
#include "server.h"
#include "User.h"

#include "reSerializer.h"

#include "reNet.h"
#include "reDB.h"
#include "reMatcher.h"
#include "reOptions.h"

#include "reLogger.h"
#include "reStats.h"
#include "reAuthorizer.h"
#include "reUser.h"

using ::testing::Return;
using ::testing::AtLeast;

// template
TEST(NetMock, TEST) {
    std::cout << "NetMock | TEST" << std::endl;
    // Arrange
    // Act
    // Assert
}

TEST(NetMock, HTTP_format) {
    std::cout << "NetMock | HTTP-format" << std::endl;

    // Arrange
    reSerializer ms;
    HTTP_format http(ms);
    EXPECT_CALL(ms, serialize("smtg")).Times(AtLeast(3));

    // Act
    http.authorize_handler();
    http.register_handler();
    http.request_handler();

    // TODO: Denis check parsing correction
    // Event res;
    // http.request_handler(res);

    // Assert
    // EXPECT_EQ();
}

TEST(NetMock, WS_format) {
    std::cout << "NetMock | WS-format" << std::endl;
    // Arrange
    reSerializer ms;
    WS_format ws(ms);
    EXPECT_CALL(ms, serialize("smtg")).Times(AtLeast(3));

    // Act

    ws.chat_handler();
    ws.game_request_handler();
    ws.game_response_handler();

    // TODO: Denactive check parsing correction
    // Event res;
    // http.request_handler(res);

    // Assert
    // EXPECT_EQ();
}

TEST(NetMock, Server) {
    std::cout << "NetMock | Server" << std::endl;
    // Arrange
    reNet mn;
    reMatcher mr;
    reOptions mo;
    Server s(mo);

    EXPECT_CALL(mo, get_info).Times(AtLeast(1)).WillOnce(Return("owner: TestOwner | ip: 000.000.000.000:0"));
    ON_CALL(mo, get_port).WillByDefault(Return(0));
    ON_CALL(mo, get_ip).WillByDefault(Return("000.000.000.000"));
    ON_CALL(mo, get_owner).WillByDefault(Return("TestOwner"));

    EXPECT_CALL(mn, accept).Times(AtLeast(1)).WillOnce(Return((Connection){ "000.000.000.000" }));

    // Act & Assert
    EXPECT_EQ(s.is_running(), false);
    s.run();
    EXPECT_EQ(s.is_running(), true);
    s.stop();
    EXPECT_EQ(s.is_running(), false);
}

TEST(NetMock, Serializer) {
    std::cout << "NetMock | Serializer" << std::endl;
    // Arrange
    JSON_serializer s;
    reAuthorizer ma;
    fakeDB mdb;
    reLogger ml;
    reStats ms;

    EXPECT_CALL(ml, log).Times(AtLeast(1));

    std::string ip ("000.000.000.000");
    Connection con = {ip};
//    IUser* fake_user = nullptr;
    UserInfo fake_user_info = {0, 0};
    ON_CALL(ma, authorize).WillByDefault(Return(nullptr));
//    ON_CALL(ms, get_user_info).WillByDefault(Return(UserInfo(0,0)));

    // Act
    std::string res_ser = s.serialize("test_data");
    std::string res_des = s.deserialize("{test_data}");

    // Assert
    EXPECT_STREQ(res_ser.c_str(), "{test_data}");
    EXPECT_STREQ(res_des.c_str(), "test_data");
}

TEST(NetMock, Authorizer) {
    std::cout << "NetMock | Authorizer" << std::endl;
    // Arrange
    Authorizer a;
    reDB mdb;
    Connection con = {"000.000.000.000"};

    EXPECT_CALL(mdb, query).Times(AtLeast(2)).WillOnce(Return("no data"));

    // Act
    IUser* res_a = a.authorize(con, mdb);
    IUser* res_r = a.registrate(con, mdb);

    // Assert
    EXPECT_EQ(res_a, nullptr);
    EXPECT_EQ(res_r, nullptr);
}

TEST(NetMock, StatsAgregator) {
    std::cout << "NetMock | StatsAgregator " << std::endl;
    // Arrange
    StatsAgregator s;
    reDB mdb;
    Connection con = {"000.000.000.000"};

    EXPECT_CALL(mdb, query).Times(AtLeast(2)).WillOnce(Return("no data"));

    // Act
    Stats res_i = s.get_user_info(0, mdb);
    Stats res_s = s.get_user_stats(0, mdb);

    UserInfo fake_i = {0};
    Stats fake_s = {0};
    // Assert
    EXPECT_EQ(res_i, fake_i);
    EXPECT_EQ(res_s, fake_s);
}
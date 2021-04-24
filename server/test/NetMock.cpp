#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "net.h"
#include "server.h"
#include "User.h"

#include "reSerializer.h"

#include "reNet.h"
#include "reOptions.h"

#include "reLogger.h"
#include "reStats.h"
#include "reAuthorizer.h"
#include "reUser.h"

using ::testing::Return;
using ::testing::AtLeast;

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
    //reUser mu;
    reAuthorizer ma;
    reLogger ml;
    //reStats rs;

    // Act
    // Assert
}
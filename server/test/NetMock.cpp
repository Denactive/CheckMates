#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "net.h"
#include "reSerializer.h"

using ::testing::Return;
using ::testing::AtLeast;

TEST(NetMock, HTTP_format) {
    std::cout << "NetMock | HTTP-format" << std::endl;

    // Arrange
    reSerializer ms;
    HTTP_format http(ms);
    EXPECT_CALL(ms, serialize("hi, http")).Times(AtLeast(3));

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
    EXPECT_CALL(ms, serialize("hello, ws")).Times(AtLeast(3));

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
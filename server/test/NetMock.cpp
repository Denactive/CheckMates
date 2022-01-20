#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "net.h"
#include "server.h"
#include "User.h"

#include "reDB.h"
#include "reGameSession.h"
#include "reLogger.h"

using ::testing::Return;
using ::testing::AtLeast;


// template
/*
TEST(NetMock, TEST) {
    std::cout << "NetMock | TEST" << std::endl;
    // Arrange
    // Act
    // Assert
}
*/

TEST(NetMock, OptionsUnit) {
    std::cout << "NetMock | Options" << std::endl;
    // Arrange
    const std::string ServerName("SaberLion-TEST");
    const std::string IP("0.0.0.0");
    std::string storage_root = "/storage";
    auto active_users = std::make_shared<UserMap>();
    std::string http_logger("http_test__logs/");
    std::string ws_logger("ws_test_logs/");

    Options opts_test_http("http", ServerName, IP, 0, storage_root, "http_test_logs");
    Options opts_test_ws("ws", ServerName, IP, 0, storage_root, "ws_test_logs");
    Server s_test_http(opts_test_http, active_users);
    Server s_test_ws(opts_test_ws, active_users);

    // Assert
    EXPECT_STREQ(opts_test_http.get_info().c_str(), "owner: SaberLion-TEST | ip: 0.0.0.0:0 (http)\ndoc dir: /storage\nlog dir: http_test_logs\n");
    EXPECT_STREQ(opts_test_ws.get_info().c_str(), "owner: SaberLion-TEST | ip: 0.0.0.0:0 (ws)\ndoc dir: /storage\nlog dir: ws_test_logs\n");
}

TEST(NetMock, DB) {
    std::cout << "NetMock | DB" << std::endl;
    // Arrange
    reDB mdb;
    reLogger ml;

    const std::string ServerName("SaberLion-TEST");
    const std::string IP("0.0.0.0");
    std::string storage_root = "/storage";
    auto active_users = std::make_shared<UserMap>();
    std::string http_logger("http_test__logs/");
    std::string ws_logger("ws_test_logs/");

    Options opts_test_http("http", ServerName, IP, 0, storage_root, "http_test_logs");
    Options opts_test_ws("ws", ServerName, IP, 0, storage_root, "ws_test_logs");
    Server s_test_http(opts_test_http, active_users);
    Server s_test_ws(opts_test_ws, active_users);

    db_error ec;
    ON_CALL(mdb, query("update", ec))
            .WillByDefault(Return("unsupported command"));

    boost::asio::io_context ioc;
    // Act

    s_test_http.run(ioc);
    s_test_ws.run(ioc);

    // Assert
}

// no sense in mock-testing
// Session - cannot be created without opened tcp-socket | only void functions
// Listener - totally boost-based
// Options - just a structure
// Matcher - gamesession creating inside
// Logger - no return value
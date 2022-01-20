cmake_minimum_required(VERSION 3.11)
project(CheckMates)
set(CMAKE_C_STANDARD 17)

# крутая компиляция для взрослых
#set(CMAKE_CXX_FLAGS "-g -coverage -O0 -Wall -fprofile-arcs -ftest-coverage -fPIC -lstdc++fs")
set(CMAKE_CXX_FLAGS "-g -std=c++17")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
set(GMock_DIR ./)
set(PROGRAM_NAME server)
set(SOURCE_DIR source)
set(LIB_DIR lib)
include_directories(source/ test/ client_example/)
add_definitions(-fprofile-arcs -ftest-coverage)

find_package(Boost)
IF (Boost_FOUND)
    message("Boost version: ${Boost_VERSION} | ${Boost_INCLUDE_DIR}")
    include_directories(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS("-DHAS_BOOST")
ENDIF()

add_executable(${PROGRAM_NAME}
        ${SOURCE_DIR}/main.cpp
        source/server.cpp
        source/matcher.cpp
        source/net.cpp
        source/community.cpp
        source/ServerDB.cpp
        source/GameSession.cpp
        test/reSerializer.h
        source/Player.cpp
        source/User.cpp
        source/King.cpp
        source/ChessBoard.cpp
        source/Chesspiece.cpp)
target_link_libraries (${PROGRAM_NAME} ${Boost_LIBRARIES} -lpthread -fprofile-arcs)

# TEST CLIENT
add_executable(client client_example/FullClient.cpp)
target_link_libraries (client ${Boost_LIBRARIES} -lpthread -fprofile-arcs)

# TESTING
enable_testing()
find_package(GTest REQUIRED)
include_directories(${INCLUDE_DIRECTORIES})
message(${GTEST_LIBRARIES})
find_package(GMock REQUIRED)
include_directories(${INCLUDE_DIRECTORIES})
message(${GMOCK_LIBRARIES})

add_executable(net_mock_test
        test/tests.cpp
        test/NetMock.cpp
        source/server.cpp
        source/matcher.cpp
        source/net.cpp
        source/community.cpp
        source/ServerDB.cpp
        source/GameSession.cpp
        test/reSerializer.h
        source/Player.cpp
        source/User.cpp
        source/King.cpp
        source/ChessBoard.cpp
        source/Chesspiece.cpp)
target_link_libraries(net_mock_test ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES} -lpthread -fprofile-arcs)
add_test(NetMockTest ./net_mock_test)

# Server Unit GTest
add_executable(server_unit_test test/ServerUnitTest.cpp)
target_link_libraries(server_unit_test ${GTEST_LIBRARIES} -lpthread -fprofile-arcs)
add_test(server_test ./server_unit_test)

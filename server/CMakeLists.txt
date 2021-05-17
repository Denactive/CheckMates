cmake_minimum_required(VERSION 3.11)
project(CheckMates)
set(CMAKE_C_STANDARD 11)

# крутая компиляция для взрослых
#set(CMAKE_CXX_FLAGS "-g -coverage -O0 -Wall -Werror -fprofile-arcs -ftest-coverage -fPIC")
set(CMAKE_CXX_FLAGS "-g -Wall ")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
set(GMock_DIR ./)
set(PROGRAM_NAME server)
set(SOURCE_DIR source)
set(LIB_DIR lib)
include_directories(source/ test/)

#find_package(Boost REQUIRED COMPONENTS system)
find_package(Boost)
IF (Boost_FOUND)
    message("Boost version: ${Boost_VERSION}")
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
        source/King.cpp
        source/TurnControl.cpp
        source/ChessBoard.cpp
        source/Chesspiece.cpp)
target_link_libraries (${PROGRAM_NAME} ${Boost_LIBRARIES} -lpthread)



enable_testing()
find_package(GTest REQUIRED)
include_directories(${INCLUDE_DIRECTORIES})
message(${GTEST_LIBRARIES})
find_package(GMock REQUIRED)
include_directories(${INCLUDE_DIRECTORIES})
message(${GMOCK_LIBRARIES})


#add_executable(test1 test/test1.cpp test/tests.cpp source/GameSession.cpp source/User.cpp source/Player.cpp test/reChessPiece.h source/community.cpp)
#target_link_libraries(test1 ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES})
#target_link_libraries (test1 ${Boost_LIBRARIES} -lpthread)

#add_executable(test2 test/test2.cpp test/tests.cpp source/GameSession.cpp source/User.cpp source/Player.cpp source/community.cpp)
#target_link_libraries(test2 ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES})
#target_link_libraries (test2 ${Boost_LIBRARIES} -lpthread)

#add_executable(net_mock_test test/NetMock.cpp test/tests.cpp source/net.cpp source/community.cpp source/GameSession.cpp source/User.cpp source/matcher.cpp source/server.cpp)
#target_link_libraries(net_mock_test ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES})
#target_link_libraries (net_mock_test ${Boost_LIBRARIES} -lpthread)

#add_executable(community_mock_test test/CommunityMock.cpp test/tests.cpp source/matcher.cpp source/GameSession.cpp source/community.cpp)
#target_link_libraries(community_mock_test ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES})
#target_link_libraries (community_mock_test ${Boost_LIBRARIES} -lpthread)

#add_executable(game_mock_test test/GameMock.cpp test/tests.cpp source/net.cpp source/community.cpp source/GameSession.cpp source/User.cpp source/matcher.cpp)
#target_link_libraries(game_mock_test ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES})
#target_link_libraries (game_mock_test ${Boost_LIBRARIES} -lpthread)

#add_test(test1 ./test1)
#add_test(test2 ./test2)
#add_test(NetMockTest ./net_mock_test)
#add_test(CommunityMockTest ./community_mock_test)
#add_test(GameMockTest ./game_mock_test)

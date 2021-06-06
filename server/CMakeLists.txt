cmake_minimum_required(VERSION 3.1)
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

#find_package(Boost REQUIRED COMPONENTS system)
find_package(Boost)
IF (Boost_FOUND)
    message("Boost version: ${Boost_VERSION} | ${Boost_INCLUDE_DIR}")
    include_directories(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS("-DHAS_BOOST")
ENDIF()

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_WIN32_THREADS_INIT 0)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)


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
        source/TurnControl.cpp
        source/ChessBoard.cpp
        source/Chesspiece.cpp)
target_link_libraries (${PROGRAM_NAME} ${Boost_LIBRARIES} -lpthread)
add_executable(client client_example/FullClient.cpp)
target_link_libraries (client ${Boost_LIBRARIES} -lpthread)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${INCLUDE_DIRECTORIES})
message(${GTEST_LIBRARIES})
find_package(GMock REQUIRED)
include_directories(${INCLUDE_DIRECTORIES})
message(${GMOCK_LIBRARIES})

add_executable(test1 test/TestPlayer.cpp test/tests.cpp source/ChessBoard.cpp)
target_link_libraries(test1 ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES})
target_link_libraries (test1 ${Boost_LIBRARIES} -lpthread)

#add_executable(test2 test/test2.cpp test/tests.cpp source/GameSession.cpp source/User.cpp source/Player.cpp source/community.cpp)
#target_link_libraries(test2 ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES})
#target_link_libraries (test2 ${Boost_LIBRARIES} -lpthread)


add_test(test1 ./test1)
#add_test(test2 ./test2)
#add_test(NetMockTest ./net_mock_test)
#add_test(CommunityMockTest ./community_mock_test)
#add_test(GameMockTest ./game_mock_test)
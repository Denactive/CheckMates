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

#find_package(Boost REQUIRED COMPONENTS system)
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
        source/TurnControl.cpp
        source/ChessBoard.cpp
        source/Chesspiece.cpp)
target_link_libraries (${PROGRAM_NAME} ${Boost_LIBRARIES} -lpthread)
add_executable(client client_example/FullClient.cpp)
target_link_libraries (client ${Boost_LIBRARIES} -lpthread)
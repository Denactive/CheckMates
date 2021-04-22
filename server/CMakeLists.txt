cmake_minimum_required(VERSION 3.11)
project(CheckMates)
set(CMAKE_C_STANDARD 11)

# крутая компиляция для взрослых
#set(CMAKE_CXX_FLAGS "-g -coverage -O0 -Wall -Werror -fprofile-arcs -ftest-coverage -fPIC")
set(CMAKE_CXX_FLAGS "-g -Wall -Werror")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
set(GMock_DIR "~/CheckMates/server")
set(PROGRAM_NAME server)
set(SOURCE_DIR source)
set(LIB_DIR lib)
include_directories(source/ test/)

find_package(Boost REQUIRED COMPONENTS system)
#find_package(Boost)
IF (Boost_FOUND)
    message("Boost version: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS("-DHAS_BOOST")
ENDIF()

add_executable(${PROGRAM_NAME}
        ${SOURCE_DIR}/main.cpp
        source/server.cpp
        source/net.cpp
        source/community.cpp
        source/ServerDB.cpp
        source/GameSession.cpp
        )
target_link_libraries (${PROGRAM_NAME} ${Boost_LIBRARIES} -lpthread)


enable_testing()
find_package(GTest REQUIRED)
include_directories(${INCLUDE_DIRECTORIES})
message(${GTEST_LIBRARIES})
find_package(GMock REQUIRED)
include_directories(${INCLUDE_DIRECTORIES})
message(${GMOCK_LIBRARIES})


add_executable(test1 test/test1.cpp test/tests.cpp source/GameSession.cpp)
target_link_libraries(test1 ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES})
target_link_libraries (test1 ${Boost_LIBRARIES} -lpthread)

add_executable(test2 test/test2.cpp test/tests.cpp source/GameSession.cpp)
target_link_libraries(test2 ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES})
target_link_libraries (test2 ${Boost_LIBRARIES} -lpthread)

add_test(test1 ./test1)
add_test(test2 ./test2)

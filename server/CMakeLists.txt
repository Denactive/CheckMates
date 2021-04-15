cmake_minimum_required(VERSION 3.16)
project(CheckMates)
set(CMAKE_C_STANDARD 11)

# крутая компиляция для взрослых
#set(CMAKE_CXX_FLAGS "-g -coverage -O0 -Wall -Werror -fprofile-arcs -ftest-coverage -fPIC")
set(CMAKE_CXX_FLAGS "-g -Wall -Werror")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

set(PROGRAM_NAME checkMatesProto)
set(SOURCE_DIR source)
set(LIB_DIR lib)
include_directories(source/ tests/)

add_executable(${PROGRAM_NAME} source/main.cpp  source/GameSession.cpp)
#target_link_libraries(${PROGRAM_NAME} word_finder_shared)

#делайте либами
#add_library(<some lib name> SHARED ${MULTITHREAD_PROJ_DIR}/_.cpp)
#target_link_libraries(${PROGRAM_NAME} )
#add_executable(program-mt ${MULTITHREAD_PROJ_DIR}/program-MT.c)

enable_testing()
find_package(GTest REQUIRED)
include_directories(${INCLUDE_DIRECTORIES})
message(${GTEST_LIBRARIES})

add_executable(test1 tests/tests.cpp tests/test1.cpp)

add_test(test1 ./test1)

cmake_minimum_required(VERSION 3.16)
project(CheckMates)
set(CMAKE_C_STANDARD 11)

# крутая компиляция для взрослых
#set(CMAKE_CXX_FLAGS "-g -coverage -O0 -Wall -Werror -fprofile-arcs -ftest-coverage -fPIC")
set(CMAKE_CXX_FLAGS "-g -Wall -Werror")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

set(PROGRAM_NAME client)
set(SOURCE_DIR source)
set(LIB_DIR lib)
include_directories(source/)

add_executable(${PROGRAM_NAME} ${SOURCE_DIR}/main.cpp source/main.cpp source/server.cpp source/server.h)
find_package(Boost REQUIRED COMPONENTS system)
#message(${BOOST_LIBRARIES})
#message(${BOOST_INCLUDE_DIRS})
target_link_libraries (${PROGRAM_NAME}
        #OpenSSL::SSL OpenSSL::Crypto
        lib-system
        lib-regex
        lib-asio
        #lib-asio-ssl
        lib-beast
)
#target_link_libraries(${PROGRAM_NAME} word_finder_shared)

#делайте либами
#add_library(<some lib name> SHARED ${MULTITHREAD_PROJ_DIR}/_.cpp)
#target_link_libraries(${PROGRAM_NAME} )
#add_executable(program-mt ${MULTITHREAD_PROJ_DIR}/program-MT.c)


#тесты
#enable_testing()
#find_package(GTest REQUIRED)

#include_directories(${GTEST_INCLUDE_DIRS})
#message(${GTEST_LIBRARIES})
#message(${GTEST_INCLUDE_DIRS})

#add_executable(tests testing/tests.cpp)
#target_link_libraries(tests ${GTEST_LIBRARIES} -lpthread)

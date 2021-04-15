cmake_minimum_required(VERSION 3.16)
project(CheckMates)
set(CMAKE_C_STANDARD 17)

# крутая компиляция для взрослых
#set(CMAKE_CXX_FLAGS "-g -coverage -O0 -Wall -Werror -fprofile-arcs -ftest-coverage -fPIC")
set(CMAKE_CXX_FLAGS "-g -Wall -Werror")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

set(PROGRAM_NAME server)
set(SOURCE_DIR source)
#set(Boost_COMPILER -gcc49)
set(LIB_DIR lib)
include_directories(source/)

#set(BOOST_ROOT /usr/include/boost)
#set(BOOST_USE_STATIC_LIBS ON)
#find_package(Boost REQUIRED COMPONENTS system thread)
find_package(Boost)
IF (Boost_FOUND)
    message("Boost version: ${Boost_VERSION}")
    message("Boost compiler version: ${Boost_COMPILER}")

    include_directories(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS("-DHAS_BOOST")
ENDIF()

add_executable(${PROGRAM_NAME}
        ${SOURCE_DIR}/main.cpp
        source/server.cpp
        source/net.cpp
        source/matcher.cpp
        source/user.cpp
        source/community.cpp
        source/ServerDB.cpp
        )
target_link_libraries (${PROGRAM_NAME} ${Boost_LIBRARIES})

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

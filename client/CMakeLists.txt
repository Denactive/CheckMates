cmake_minimum_required(VERSION 3.5)

project(client LANGUAGES CXX)
set(GMock_DIR "./")

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "--coverage -Wall")
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
message(${GTEST_LIBRARIES})
find_package(GMock REQUIRED)
include_directories(${INCLUDE_DIRECTORIES})
message(${GMOCK_LIBRARIES})

find_package(Boost REQUIRED COMPONENTS system)
#find_package(Boost)
IF (Boost_FOUND)
    message("Boost version: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIR})
    ADD_DEFINITIONS("-DHAS_BOOST")
ENDIF()

#configure_file(CMakeLists.txt.in
#        googletest-download/CMakeLists.txt)
#execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
#        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
#execute_process(COMMAND ${CMAKE_COMMAND} --build .
#        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )

#add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
#        ${CMAKE_BINARY_DIR}/googletest-build)

#enable_testing()
#add_subdirectory(tests)

find_package(QT NAMES Qt6 Qt5 COMPONENTS 3rdparty Widgets Core Quick Sql Network LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Core Quick Sql Network LinguistTools REQUIRED)

set(PROJECT_SOURCES
        main.cpp

        include/wsclient.h

        src/wsclient.cpp
        src/serverconnection.cpp
        src/graphics.cpp
        src/chessboard.cpp
        src/cell.cpp
        src/community.cpp
        src/database.cpp
        src/figures.cpp
        src/gameobjects.cpp

        src/windows/mainwindow.cpp
        src/windows/chatwindow.cpp
        src/windows/gamewindow.cpp
        src/windows/menuwindow.cpp
        src/windows/settingswindow.cpp
        src/windows/authorizerwindow.cpp


        include/serverconnection.h
        include/graphics.h
        include/chessboard.h
        include/cell.h
        include/community.h
        include/database.h
        include/figures.h
        include/gameobjects.h

        include/windows/mainwindow.h
        include/windows/chatwindow.h
        include/windows/gamewindow.h
        include/windows/menuwindow.h
        include/windows/settingswindow.h
        include/windows/authorizerwindow.h

        ${TS_FILES}
)

add_library(clientlib SHARED ${PROJECT_SOURCES})
target_link_libraries(clientlib Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::Sql Qt${QT_VERSION_MAJOR}::Network
    GTest::GTest GTest::Main)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(client ${PROJECT_SOURCES})
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    add_executable(client ${PROJECT_SOURCES}})
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(client PRIVATE clientlib)

add_executable(server_connect server_connect/BoostExampleClient.cpp)
target_link_libraries (server_connect ${Boost_LIBRARIES} -lpthread)




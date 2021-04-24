set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)
include_directories({PROJECT_SOURCE_DIR}/)
include_directories({PROJECT_SOURCE_DIR}/src)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)



add_executable(test1 tst_community.cpp ../include/community.h main.cpp ../src/community.cpp)
target_link_libraries(test1 ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES})
target_link_libraries (test1 ${Boost_LIBRARIES} -lpthread)

add_executable(test2 tst_database.cpp ../include/database.h main.cpp ../src/database.cpp
    ../include/community.h ../src/community.cpp)
target_link_libraries(test2 ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES})
target_link_libraries (test2 ${Boost_LIBRARIES} -lpthread)

#add_executable(test3 tst_chessboard.cpp ../include/chessboard.h main.cpp ../src/chessboard.cpp ../include/figures.h ../src/figures.cpp)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(test3 tst_chessboard.cpp ../include/chessboard.h main.cpp ../src/chessboard.cpp ../include/figures.h ../src/figures.cpp)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    add_executable(test3 tst_chessboard.cpp ../include/chessboard.h main.cpp ../src/chessboard.cpp ../include/figures.h ../src/figures.cpp)
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()
target_link_libraries(test3 ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES} Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries (test3 ${Boost_LIBRARIES} -lpthread)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(test4 tst_graphics_main.cpp ../graphics.h main.cpp ../src/graphics.cpp
        ../include/gamewindowswork.h ../src/gamewindowswork.cpp ../include/community.h main.cpp ../src/community.cpp)
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    add_executable(test4 tst_graphics_main.cpp ../graphics.h main.cpp ../src/graphics.cpp
        ../include/gamewindowswork.h ../src/gamewindowswork.cpp ../include/community.h main.cpp ../src/community.cpp)
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()
target_link_libraries(test4 ${GTEST_LIBRARIES} ${GMOCK_LIBRARIES} Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries (test4 ${Boost_LIBRARIES} -lpthread)

add_test(test1 ./test1)
add_test(test2 ./test2)
add_test(test3 ./test3)
add_test(test4 ./test4)

include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
#CONFIG -= qt

INCLUDEPATH += "../"

HEADERS += \
        tst_test.h \
        ../include/database.h \
        ../include/chessboard.h \
        ../include/community.h \
        ../include/figures.h \
        ../include/graphics.h \
        ../my_tests/tests.h


SOURCES += \
        main.cpp \
        ../src/database.cpp \
        ../src/chessboard.cpp \
        ../src/community.cpp \
        ../src/graphics.cpp \
        ../src/main.cpp \

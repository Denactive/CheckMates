include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
#CONFIG -= qt

QT += quick
QT += quickwidgets
QT += core gui

#CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        src/database.cpp \
        src/chessboard.cpp \
        src/community.cpp \
        src/figures.cpp \
        src/gamewindowswork.cpp \
        src/graphics.cpp \
        src/main.cpp \
        src/mainwindow.cpp

RESOURCES += qml.qrc \

TRANSLATIONS += \
    qtChess_ru_RU.ts

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    include/database.h \
    include/chessboard.h \
    include/community.h \
    include/figures.h \
    include/gamewindowswork.h \
    include/graphics.h \
    include/mainwindow.h \
    my_tests/tests.h

FORMS += \
    ui/mainwindow.ui

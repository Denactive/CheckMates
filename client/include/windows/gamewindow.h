#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <thread>

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QListWidget>
#include <QAbstractListModel>
#include <QStackedWidget>
#include <QGridLayout>
#include <QLabel>
#include <QTime>
#include <QTimer>

#include "include/community.h"
#include "include/figures.h"
#include "include/gameobjects.h"
#include "include/chessboard.h"
#include "include/database.h"
#include "include/graphics.h"

#include "include/wsclient.h"

class IGameWindow {

public:
    virtual bool moveFigure(Figure *figure) = 0;
    virtual QVBoxLayout* drawChat(Chat * chat) = 0;
    virtual void offerDraw() = 0;
    virtual void surrender() = 0;
    virtual void sendClicked() = 0;
    virtual QVBoxLayout* playerStatisticsDraw() = 0;
};

class GameWindow :  public QWidget, public IGameWindow {
    Q_OBJECT

public:
    GameWindow(QWidget * parent = nullptr, QStackedWidget * main = nullptr, std::shared_ptr<GameInfo> gameInfo = std::make_shared<GameInfo>(),
               std::shared_ptr<User> opponent = std::make_shared<User>(), GlobalNet *globalNet = nullptr);
    void checkGame();
    bool moveFigure(Figure *figure) override { return true; };
    QWidget* drawGameChat();
    void drawGameTop();
    QVBoxLayout* playerStatisticsDraw();
    QVBoxLayout* drawChat(Chat *chat = nullptr) override;
    void drawGame();

public slots:
    void surrender() override;
    void offerDraw() override;
    void sendClicked() override;
    void slotTimerAlarm();

private:
    std::shared_ptr<GameInfo> gameInfo;
    std::shared_ptr<User> opponent;

    QStackedWidget * main;
    QVBoxLayout *game;
    QListWidget * gameChat;
    QLineEdit * writeMessage;
    QLabel *gameMessage;
    QLabel * gameTime;

    GlobalNet *globalNet;
};
#endif // GAMEWINDOW_H

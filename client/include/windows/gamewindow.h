#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

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
// fliker free i двойная буферизация flickerfree, double buffering

#include "include/community.h"
#include "include/figures.h"
#include "include/gameobjects.h"
#include "include/chessboard.h"


class IGameWindow {

public:
    virtual bool moveFigure(Figure *figure) = 0;
    virtual QVBoxLayout* drawChat(Chat * chat) = 0;
    virtual void offerDraw() = 0;
    virtual void surrender() = 0;
    virtual void sendClicked() = 0;
    virtual QVBoxLayout* playerStatisticsDraw(User & user) = 0;
};

class GameWindow :  public QWidget, public IGameWindow {
    Q_OBJECT

public:
    GameWindow(QWidget * parent = nullptr, QStackedWidget * main = nullptr, bool isPlayer = true, bool isKingUnderMat = false);
    bool moveFigure(Figure *figure) override { return true; };
    QWidget* drawGameChat();
    void drawGameTop();
    QVBoxLayout* playerStatisticsDraw(User & user);
    QVBoxLayout* drawChat(Chat *chat = nullptr) override;

    void resizeEvent(QResizeEvent * event);

public slots:
    void surrender() override;
    void offerDraw() override;
    void sendClicked() override;
    void slotTimerAlarm();

private:
    bool isPlayer; // true - action (check cell) from you, false - action (check cell) from friend
    bool isOfferDraw; // if false -> back to menu (after action surrender or offer Draw) - тут скорее принял друг предложение о ничье или нет
    bool isKingUnderMat;

    QStackedWidget * main;
    QVBoxLayout *game;
    QListWidget * gameChat;
    QLineEdit * writeMessage;
    QLabel *gameMessage;
    QLabel * gameTime;

    // QLabel * spacer;
    //ChessBoard *board;
    //std::pair<int,int> size;
};
#endif // GAMEWINDOW_H

#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QListWidget>
#include <QAbstractListModel>
#include <QStackedWidget>
#include <QGridLayout>

#include "include/community.h"
#include "include/figures.h"

class IGameWindow {

public:
    virtual void drawChessBoard() = 0;
    virtual bool moveFigure(Figure *figure) = 0;
    virtual void drawChat(Chat * chat) = 0;
    virtual void drawSendButton(MyMessage *message = nullptr) = 0;
    virtual void offerDraw() = 0;
    virtual void surrender() = 0;
    virtual void sendClicked() = 0;
};

class GameWindow :  public QWidget, public IGameWindow {
    Q_OBJECT

public:
    GameWindow(QWidget * parent = nullptr, QStackedWidget * main = nullptr);
    void drawChessBoard() override;
    bool moveFigure(Figure *figure) override { return true; };
    void drawChat(Chat *chat = nullptr) override;
    void drawSendButton(MyMessage *message = nullptr);

public slots:
    void surrender() override;
    void offerDraw() override;
    void sendClicked() override;

private:
    QStackedWidget * main;
    QGridLayout *game;
    QListWidget * gameChat;
    QLineEdit * writeMessage;
};

#endif // GAMEWINDOW_H

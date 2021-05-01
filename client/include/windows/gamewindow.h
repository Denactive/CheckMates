#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include "../include/community.h"
#include "../include/chessboard.h"
#include "../include/figures.h"
#include "../include/gameobjects.h"
#include "../include/windows/mainwindow.h"
#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QListWidget>
#include <QAbstractListModel>
#include <QStackedWidget>
#include <QGridLayout>

class Figure;
class Chat;
class Message;
class User;

class IGameWindow {

public:
    virtual void drawChessBoard() = 0;
    virtual bool moveFigure(Figure *figure) = 0;
    virtual void drawChat(Chat *chat) = 0;
    //virtual bool sendMessage(MyMessage *message)= 0;
    virtual void offerDraw() = 0;
    virtual void surrender() = 0;
};

class GameWindow :  public QWidget, public IGameWindow {
    Q_OBJECT
private slots:
    void sendClicked();

public:
    GameWindow(QWidget * parent = nullptr, QStackedWidget * main = nullptr);
    void drawChessBoard() override {};
    bool moveFigure(Figure *figure) override { return true; };
    void drawChat(Chat *chat) override {};
    //bool sendMessage(MyMessage * message) override { return true; };

public slots:
    void surrender() override;
    void offerDraw() override;

private:
    QStackedWidget * main;

    bool isMatching;
    QList<Chat*> chats;
    QList<User*> users;
};

#endif // GAMEWINDOW_H

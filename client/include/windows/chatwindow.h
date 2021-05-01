#ifndef CHATWINDOW_H
#define CHATWINDOW_H

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

class Figure;
class Chat;
class Message;
class User;

class IChatWindow {
public:
    virtual void drawUserSettings() = 0;
    virtual void drawMessages() = 0;
    virtual bool sendMessage() = 0;
    virtual bool backToMenu() = 0;
};

class ChatWindow : public IChatWindow {
public:
    ChatWindow(Chat * chat = nullptr): chat(chat) {}
    void drawUserSettings() override {}
    void drawMessages() override {}
    bool sendMessage() override { return true; }
    bool backToMenu() override { return true; }
private:
    Chat * chat;
};

#endif // CHATWINDOW_H

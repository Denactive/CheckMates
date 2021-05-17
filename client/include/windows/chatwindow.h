#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QListWidget>
#include <QAbstractListModel>
#include <QStackedWidget>
#include <QLayout>
#include <QDebug>
#include <QMessageBox>

#include "include/community.h"
#include "include/gameobjects.h"

class Figure;
class Chat;
class Message;
class User;

class IChatWindow {
public:
    virtual void drawUserSettings() = 0;
    virtual void drawMessages() = 0;
    virtual bool sendMessage() = 0;
    virtual void setChat(Chat * chat) = 0;

};

class ChatWindow : public QWidget, public IChatWindow {
    Q_OBJECT
public:
    ChatWindow(QWidget * parent = nullptr, QStackedWidget * main = nullptr, Chat * chat = nullptr);
    void drawUserSettings() override {}
    void drawMessages() override {}
    bool sendMessage() override { return true; }
    void setChat(Chat * chat) override { this->chat = chat; }

public slots:
    void backToMenu();
private:
    QStackedWidget * main;
    Chat * chat;

    QVBoxLayout *chatMenu;
};


#endif // CHATWINDOW_H

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
#include <memory>

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
    virtual void setChat(std::shared_ptr<Chat> newChat) = 0;

};

class ChatWindow : public QWidget, public IChatWindow {
    Q_OBJECT
public:
    ChatWindow(QWidget * parent = nullptr, QStackedWidget * main = nullptr, std::shared_ptr<Chat> chat = std::make_shared<Chat>());
    void drawUserSettings() override {}
    void drawMessages() override {}
    bool sendMessage() override { return true; }
    void setChat(std::shared_ptr<Chat> newChat) override { this->chat = newChat; }

public slots:
    void backToMenu();
private:
    QStackedWidget * main;
    std::shared_ptr<Chat> chat;

    QVBoxLayout *chatMenu;
};


#endif // CHATWINDOW_H

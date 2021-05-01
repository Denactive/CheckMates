#ifndef MENUWINDOW_H
#define MENUWINDOW_H
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

class IMenuWindow {
public:
    virtual void drawMessages() = 0;
    virtual void drawFriends() = 0;
    virtual void tapPlay() = 0;
    virtual bool turnOnMatching()= 0;
    virtual User * chooseFriend() = 0;
    virtual Chat * chooseChat() = 0;
};

class MenuWindow : public QWidget, public IMenuWindow {
    Q_OBJECT
public:
    MenuWindow(QWidget * parent = nullptr, QStackedWidget * main = nullptr, bool isMatching = false);
    void drawMessages() override {};
    void drawFriends() override {};
    bool turnOnMatching() override { return true; }
    User * chooseFriend() override { return nullptr; }
    Chat * chooseChat() override { return nullptr; }

public slots:
    void tapPlay() override;

private:
    QStackedWidget * main;

    bool isMatching;
    QList<Chat*> chats;
    QList<User*> users;
};

#endif // MENUWINDOW_H

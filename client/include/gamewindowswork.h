#ifndef GAMEWINDOWSWORK_H
#define GAMEWINDOWSWORK_H
//#include "../graphics.h"
#include "../include/community.h"
#include "../include/chessboard.h"
#include "../include/figures.h"
#include "../include/gameobjects.h"
#include "../mainwindow.h"
#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QListWidget>
#include <QAbstractListModel>
#include <QStackedWidget>

//namespace Ui {
//    class MainWindow;
//}

class Figure;
class Chat;
class Message;
class User;

class IGame {
public:
    virtual void drawChessBoard() = 0;
    virtual bool moveFigure(Figure *figure) = 0;
    virtual void drawChat(Chat *chat) = 0;
    virtual bool sendMessage(MyMessage *message)= 0;
    virtual bool offerDraw() = 0;
    virtual bool surrender() = 0;
};

class Game :  public IGame, public QWidget {
public:
    Game(QWidget * parent = nullptr);
    void drawChessBoard() override {};
    bool moveFigure(Figure *figure) override { return true; };
    void drawChat(Chat *chat) override {};
    bool sendMessage(MyMessage * message) override { return true; }
    bool offerDraw() override { return true; }
    bool surrender() override { return true; }

private slots:
    void sendClicked();
private:
    bool isMatching;
    QList<Chat*> chats;
    QList<User*> users;

    MyButton* createButton(const QString &text ="", const char * member = nullptr);
};

class IMenu {
public:
    virtual void drawMessages() = 0;
    virtual void drawFriends() = 0;
    virtual bool tapPlay() = 0;
    virtual bool turnOnMatching()= 0;
    virtual User * chooseFriend() = 0;
    virtual Chat * chooseChat() = 0;
};

class Menu : public IMenu {
public:
    Menu(bool isMatching = false): isMatching(isMatching) {}
    void drawMessages() override {};
    void drawFriends() override {};
    bool tapPlay() override { return true; }
    bool turnOnMatching() override { return true; }
    User * chooseFriend() override { return nullptr; }
    Chat * chooseChat() override { return nullptr; }

private:
    bool isMatching;
    QList<Chat*> chats;
    QList<User*> users;
};

class IUserSettings {
public:
    virtual void drawUserSettings() = 0;
    virtual bool changeSettings() = 0;
    virtual bool saveSettings() = 0;
    virtual bool chooseUserPhoto() = 0;
};

class UserSettings : public IUserSettings {
public:
    UserSettings(User * user = nullptr): user(user) {}
    void drawUserSettings() override {}
    bool changeSettings() override { return true; }
    bool saveSettings() override { return true; }
    bool chooseUserPhoto() override { return true; }
private:
    User * user;
};

class IAuthorizer {
public:
    virtual void drawForm() = 0;
    virtual bool sendMessage(MyMessage *message) = 0;
    virtual bool checkFromOnValid(User *user) = 0;
};

class Authorizer : public IAuthorizer {
public:
    Authorizer(bool isValid = false): isValid(isValid) {}
    void drawForm() override {}
    bool sendMessage(MyMessage *message) override { return true; }
    bool checkFromOnValid(User *user) override { return true; }
private:
    bool isValid;
};

class IChatMenu {
public:
    virtual void drawUserSettings() = 0;
    virtual void drawMessages() = 0;
    virtual bool sendMessage() = 0;
    virtual bool backToMenu() = 0;
};

class ChatMenu : public IChatMenu {
public:
    ChatMenu(Chat * chat = nullptr): chat(chat) {}
    void drawUserSettings() override {}
    void drawMessages() override {}
    bool sendMessage() override { return true; }
    bool backToMenu() override { return true; }
private:
    Chat * chat;
};

#endif // GAMEWINDOWSWORK_H

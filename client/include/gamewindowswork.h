#ifndef GAMEWINDOWSWORK_H
#define GAMEWINDOWSWORK_H
#include "graphics.h"

namespace Ui {
    class MainWindow;
}

class Figure;
class Chat;
class Message;
class User;

class IGame {
public:
    virtual void drawChessBoard() = 0;
    virtual void moveFigure(std::pair<int, int> pair, Figure &) = 0;
    virtual void drawChat(Chat &) = 0;
    virtual void sendMessage(Message & message)= 0;
    virtual bool offerDraw() = 0;
    virtual bool surrender() = 0;
};

class Game : public IGame {
public:
    void drawChessBoard() override;
    void moveFigure(std::pair<int, int> pair, Figure &) override;
    void drawChat(Chat &) override;
    void sendMessage(Message & message) override;
    bool offerDraw() override;
    bool surrender() override;
private:
    bool isMatching;
    QList<Chat*> chats;
    QList<User*> users;
    Ui::MainWindow *ui;
};

class IMenu {
public:
    virtual void drawMessages() = 0;
    virtual bool drawFriends() = 0;
    virtual void tapPlay() = 0;
    virtual void turnOnMatching()= 0;
    virtual User * chooseFriend() = 0;
    virtual Chat * chooseChat() = 0;
};

class Menu : public IMenu {
public:
    void drawMessages() override;
    bool drawFriends() override;
    void tapPlay() override;
    void turnOnMatching() override;
    User * chooseFriend() override;
    Chat * chooseChat() override;
private:
    bool isMatching;
    QList<Chat*> chats;
    QList<User*> users;
    Ui::MainWindow *ui;
};

class IUserSettings {
public:
    virtual void drawUserSettings() = 0;
    virtual bool changeSettings() = 0;
    virtual void saveSettings() = 0;
    virtual void chooseUserPhoto() = 0;
};

class UserSettings : public IUserSettings {
public:
    void drawUserSettings() override;
    bool changeSettings() override;
    void saveSettings() override;
    void chooseUserPhoto() override;
private:
    User * user;
    Ui::MainWindow *ui;
};

class IAuthorizer {
public:
    virtual void drawForm() = 0;
    virtual void sendMessage(Message & message) = 0;
    virtual bool checkFromOnValid(User & user) = 0;
};

class Authorizer : public IAuthorizer {
public:
    void drawForm() override;
    void sendMessage(Message & message) override;
    bool checkFromOnValid(User & user) override;
private:
    bool isValid;
    Ui::MainWindow *ui;
};

class IChatMenu {
public:
    virtual void drawMessages() = 0;
    virtual bool sendMessage() = 0;
    virtual void backToMenu() = 0;
};

class ChatMenu : public IChatMenu {
public:
    void drawMessages() override;
    bool sendMessage() override;
    void backToMenu() override;
private:
    Chat * chat;
    Ui::MainWindow *ui;
};

#endif // GAMEWINDOWSWORK_H

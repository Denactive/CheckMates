#ifndef MENUWINDOW_H
#define MENUWINDOW_H
#define DEBUG 0

#include <algorithm>
#include <iterator>

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QListWidget>
#include <QAbstractListModel>
#include <QStackedWidget>
#include <QGridLayout>
#include <QCheckBox>

#include <QApplication>
#include <QDesktopWidget>
#include <QMainWindow>

#include <string>
#include <memory>
#include <iostream>
#include "include/community.h"
#include "include/windows/chatwindow.h"
#include "include/database.h"
#include "include/windows/gamewindow.h"
#include "include/graphics.h"

class IMenuWindow {
public:
    virtual void drawChats(std::vector<std::shared_ptr<Chat>> chatInfo) = 0;
    virtual void drawFriends(std::vector<std::shared_ptr<User>> friendsInfo) = 0;
    virtual void tapPlay() = 0;
    virtual bool turnOnMatching()= 0;
    virtual void chooseFriend() = 0;
    virtual void chooseChat() = 0;
};

class MenuWindow : public QWidget, public IMenuWindow {
    Q_OBJECT
public:
    MenuWindow(QWidget * parent = nullptr, QStackedWidget * main = nullptr, bool isMatching = false,
               std::vector<std::shared_ptr<Chat>> chatInfo = {}, std::vector<std::shared_ptr<User>> friendsInfo = {},
               std::shared_ptr<GameInfo> gameInfo = {},  std::shared_ptr<User> opponent = nullptr, std::vector<std::shared_ptr<User>> frnsInfo = {},
               GlobalNet *globalNet = nullptr, std::shared_ptr<std::string> token = nullptr);
    void drawChats(std::vector<std::shared_ptr<Chat>> chatInfo) override;
    void drawMiddle();
    void drawFriends(std::vector<std::shared_ptr<User>> friendsInfo) override;
    bool turnOnMatching() override { return true; }

    void addFriend(size_t index, std::vector<std::shared_ptr<User>> friendsInfo);
    void addChat(size_t index, std::vector<std::shared_ptr<Chat>> chatInfo);
    void resizeEvent(QResizeEvent * event);

public slots:
    void tapPlay() override;
    void beginGame();

    void chooseFriend() override;
    void chooseChat() override;
    void changeMatching();
    void searchFriend() {}
    void searchChat() {}

private:
    QStackedWidget * main;
    QHBoxLayout *menu;

    bool isMatching;
    QCheckBox *isMatchingBox;

    QLineEdit *searchChatLine;
    QLineEdit *searchFriendLine;

    QList<FrameButton*> chats; // info from Chat
    QList<FrameButton*> friends; // info from User

    std::shared_ptr<GameInfo> gameInfo;
    QCheckBox *choosenFriend;
    std::vector<std::shared_ptr<User>> friendsInfo;
    std::shared_ptr<User> opponent;
    std::vector<std::shared_ptr<Chat>> chatInfo;

    MyButton * playButton;
    LabelImage * previewLabelImage;

    GlobalNet *globalNet;
    std::shared_ptr<std::string> token_;
};

#endif // MENUWINDOW_H

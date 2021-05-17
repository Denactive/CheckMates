#ifndef MENUWINDOW_H
#define MENUWINDOW_H
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

#include "include/community.h"
#include "include/windows/chatwindow.h"

class IMenuWindow {
public:
    virtual void drawChats(std::vector<std::shared_ptr<Chat>> chatInfo) = 0;
    virtual void drawFriends(std::vector<User*> friendsInfo) = 0;
    virtual void tapPlay() = 0;
    virtual bool turnOnMatching()= 0;
    virtual void chooseFriend() = 0;
    virtual void chooseChat() = 0;
};

class MenuWindow : public QWidget, public IMenuWindow {
    Q_OBJECT
public:
    MenuWindow(QWidget * parent = nullptr, QStackedWidget * main = nullptr, bool isMatching = false,
               std::vector<std::shared_ptr<Chat>> chatInfo = {}, std::vector<User*> friendsInfo = {});
    void drawChats(std::vector<std::shared_ptr<Chat>> chatInfo) override;
    void drawMiddle();
    void drawFriends(std::vector<User*> friendsInfo) override;
    bool turnOnMatching() override { return true; }

    void addFriend(size_t index, std::vector<User*> friendsInfo);
    void addChat(size_t index, std::vector<std::shared_ptr<Chat>> chatInfo);
    void resizeEvent(QResizeEvent * event);

public slots:
    void tapPlay() override;
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

    QList<ChatButton*> chats; // info from Chat
    QList<QFrame*> friends; // info from User

    int choosenFriendIndex;
    QCheckBox *choosenFriend;
    std::vector<std::shared_ptr<Chat>> chatInfo;

    MyButton * playButton;
    LabelImage * previewLabelImage;
};

#endif // MENUWINDOW_H

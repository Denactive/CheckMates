#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QDialog>
#include <QStackedWidget>
#include <QDebug>
#include <QObject>
#include <QComboBox>

#include "include/graphics.h"
#include "include/gameobjects.h"
#include "include/chessboard.h"

#include "include/windows/menuwindow.h"
#include "include/windows/authorizerwindow.h"
#include "include/windows/chatwindow.h"
#include "include/windows/settingswindow.h"
#include "include/windows/gamewindow.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget * parent = 0);
    ~MainWindow();
    void drawTop();
    void drawBottom();

    void drawUserIcon(User * user);
    void changeSettings(User & user);
    void printTopUsers(User * users);
    void GameInfo();

private slots:
    void onSearchChatClicked();

    void communityClicked();
    void settingsClicked();
    void aboutClicked();
    void developersClicked();
    void donateClicked();
    void contactsClicked();
    void exitClicked();
private:
    QStackedWidget * main;
    QVBoxLayout *mainLayout;

    MyButton* createButton(const QString &text ="", const char * member = nullptr);
    QString heart = QChar(0x00002764);

    std::vector<User*> topUsersInfo;
    QComboBox *topUsers;

    User *infoAboutMe;
};

#endif // MAINWINDOW_H

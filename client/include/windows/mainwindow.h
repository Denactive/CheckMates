#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <vector>
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

#include <QKeyEvent>
#include <QMessageBox>
#include <QPixmap>
#include <QToolButton>
#include <QApplication>

#include "include/graphics.h"
#include "include/gameobjects.h"
#include "include/chessboard.h"
#include "include/database.h"

#include "include/windows/menuwindow.h"
#include "include/windows/authorizerwindow.h"
#include "include/windows/chatwindow.h"
#include "include/windows/settingswindow.h"
#include "include/windows/gamewindow.h"
// #include "include/serverconnection.h"

#include <memory>
#include <string>
#include <iostream>

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(std::shared_ptr<Database> db, GlobalNet *globalNet = nullptr, QWidget * parent = 0);
    ~MainWindow();
    void drawTop();
    void drawBottom();

    void drawUserIcon(User * user);
    void changeSettings(User & user);
    void printTopUsers(User * users);

    void setRegisterUser(int index);

//    template<typename TSignal>
//    void waitingFor(TSignal&& signal)
//    {
//        QEventLoop evloop;
//        connect(this, signal, &evloop, &QEventLoop::quit);
//        evloop.exec();
//    }

signals:
    void onSaveToken();

private slots:
    void onSearchChatClicked();

    void communityClicked();
    void settingsClicked();
    void aboutClicked();
    void developersClicked();
    void donateClicked();
    void contactsClicked();
    void exitClicked();
    void logoutClicked();
    void loginClicked();
    void saveToken();
    void registrClicked();
private:
    QStackedWidget * main;
    QVBoxLayout *mainLayout;

    MyButton* createButton(const QString &text ="", const char * member = nullptr);
    QString heart = QChar(0x00002764);

    std::vector<std::shared_ptr<User>> topUsersInfo;
    QComboBox *topUsers;

    QWidget *authorizerIs;
    QWidget *authorizerNo;
    std::shared_ptr<User> infoAboutMe;

    std::vector<UserInfo> usrsInfo;
    std::vector<UserInfo>  frnsInfo;

    std::vector<std::shared_ptr<User>> friendsInfo;
    std::shared_ptr<User> opponent;

    std::shared_ptr<Database> db;
    GlobalNet *globalNet;
    std::shared_ptr<std::string> token_;
};

#endif // MAINWINDOW_H

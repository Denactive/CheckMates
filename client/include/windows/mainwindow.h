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


class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(std::shared_ptr<Database> db, QWidget * parent = 0);
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

    std::vector<std::shared_ptr<User>> topUsersInfo;
    QComboBox *topUsers;

    std::shared_ptr<User> infoAboutMe;

    std::shared_ptr<Database> db;
};

#endif // MAINWINDOW_H

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
#include "../include/graphics.h"
#include "../include/gameobjects.h"
#include "../include/chessboard.h"

#include "../include/windows/menuwindow.h"
#include "../include/windows/authorizerwindow.h"
#include "../include/windows/chatwindow.h"
#include "../include/windows/settingswindow.h"
#include "../include/windows/gamewindow.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();
    void drawTop();
    void drawButtons();
    void drawUserIcon(User * user);
    void changeSettings(User & user);
    void printTopUsers(User * users);
    void GameInfo();

protected:
    bool eventListener(QObject *watched, QEvent *event);

private slots:
    void onSearchChatClicked();

    void topPlayersClicked();
    void communityClicked();
    void settingsClicked();
    void aboutClicked();
    void developersClicked();
    void donateClicked();
    void contactsClicked();
    void exitClicked();
private:
    QStackedWidget * main;

    QString m_operation;
    QLineEdit* m_lineup;
    QLineEdit* m_linedown;
    QLabel* m_sign;

    QString heart = QChar(0x00002764);

    MyButton* createButton(const QString &text ="", const char * member = nullptr);
};







// practice

class Info : public QWidget
{
    Q_OBJECT

public:
    Info(QWidget *parent = nullptr):QWidget(parent) {
        setStyleSheet("background-color: green;");
        QGridLayout * grid = new QGridLayout();
        QLabel * label = new QLabel("info");
        grid->addWidget(label);
        setLayout(grid);
    };
    ~Info() {}

private slots:

private:

};

class Settings : public QWidget
{
    Q_OBJECT

private:
    QStackedWidget * main;

private slots:
    void backClicked() { main->setCurrentIndex(1); qDebug() << "s -> info\n"; }

public:
    Settings(QWidget *parent = nullptr, QStackedWidget * main = nullptr):QWidget(parent), main(main) {
        setStyleSheet("background-color: blue;");
        QGridLayout * grid = new QGridLayout();
        QLabel * label = new QLabel("settings");
        grid->addWidget(label);

        MyButton * backButton = new MyButton("Back");
        connect(backButton, SIGNAL(clicked()), this, SLOT(backClicked()));
        grid->addWidget(backButton);


        setLayout(grid);


    }
    ~Settings() {}

private slots:

};

class App : public QWidget
{
    Q_OBJECT
private:
    //Settings settings;
    //Info info;
    QStackedWidget * main;

    MyButton* createButton(const QString &text ="", const char * member = nullptr);

private slots:
    void settingsClicked() { main->setCurrentIndex(0); qDebug() << "m -> settings\n"; }
    void infoClicked() { main->setCurrentIndex(1); qDebug() << "m -> info\n"; }
public:
    App(QWidget *parent = nullptr):QWidget(parent) {
        QGridLayout * base = new QGridLayout();
        main = new QStackedWidget();
        setWindowTitle("App");
        setStyleSheet("background-color: lightblue;");
        //addWidget(&settings);
        //addWidget(&info);
        Settings * settings = new Settings(this, main);
        Info * info = new Info(this);

        //connect(settings, SIGNAL(clicked()), this, SLOT(settingsClicked()));
        main->addWidget(settings);


        //connect(info, SIGNAL(finished()), this, SLOT(infoClicked()));
        main->addWidget(info);


        base->addWidget(main);

        MyButton * settingsButton = new MyButton("Settings");
        connect(settingsButton, SIGNAL(clicked()), this, SLOT(settingsClicked()));
        base->addWidget(settingsButton);

        MyButton * infoButton = new MyButton("Info");
        connect(infoButton, SIGNAL(clicked()), this, SLOT(infoClicked()));
        base->addWidget(infoButton);

        setLayout(base);
    };
    ~App() {}

};


#endif // MAINWINDOW_H

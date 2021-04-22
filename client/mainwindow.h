#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "graphics.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void pushBoard();
    void drawTop();
    void drawButtons();
    void drawUserIcon(User * user);
    void changeSettings(User & user);
    void printTopUsers(User * users);
    void GameInfo();

protected:
    bool eventListener(QObject *watched, QEvent *event);

private slots:
    void on_playButton_clicked();
    void on_pushButton_clicked();
    void on_QuitButton_clicked();
    void on_searchChatButton_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

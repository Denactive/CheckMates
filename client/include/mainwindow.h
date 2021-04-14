#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "graphics.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void pushBoard();
    ~MainWindow();
    void drawTop();
    void drawButtons();
    void drawUserIcon(User * user);
    void changeSettings(User & user);
    void printTopUsers(User * users);
    void GameInfo();

private slots:
    void on_buttonSend_clicked();
    void on_surrender_clicked();
    void on_quit_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

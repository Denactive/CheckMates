#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include "graphics.h"
#include "include/gameobjects.h"
#include "include/chessboard.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QWidget // : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();//(QWidget *parent = nullptr);
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
    void on_playButton_clicked();
    void on_pushButton_clicked();
    void on_QuitButton_clicked();
    void on_searchChatButton_clicked();

    void topPlayersClicked();
    void communityClicked();
    void settingsClicked();
    void aboutClicked();
    void developersClicked();
    void donateClicked();
    void contactsClicked();
    void exitClicked();
private:
    Ui::MainWindow *ui;

    // practice
    MyButton* createButton(const QString &text, const char * member);

    //Cell* m_cells[64];

    QString m_operation;
    QLineEdit* m_lineup;
    QLineEdit* m_linedown;
    QLabel* m_sign;

    QString heart = QChar(0x00002764);
};

#endif // MAINWINDOW_H

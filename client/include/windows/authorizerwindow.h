#ifndef AUTHORIZERWINDOW_H
#define AUTHORIZERWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QListWidget>
#include <QAbstractListModel>
#include <QStackedWidget>
#include <QLayout>
#include <QDebug>
#include <QMessageBox>

#include "include/community.h"
#include "include/gameobjects.h"

class IAuthorizerWindow {
public:
    virtual void drawForm() = 0;
    virtual bool sendMessage(MyMessage *message) = 0;
    virtual bool checkFromOnValid(User *user) = 0;
};

class AuthorizerWindow : public QWidget, public IAuthorizerWindow {
public:
    AuthorizerWindow(QWidget * parent = nullptr, QStackedWidget * main = nullptr, bool isValid = false);
    void drawForm() override {}
    bool sendMessage(MyMessage *message) override { return true; }
    bool checkFromOnValid(User *user) override { return true; }

public slots:
    void backToMenu();
private:
    QStackedWidget * main;
    bool isValid;

    QVBoxLayout *authorizerMenu;
};

#endif // AUTHORIZERWINDOW_H

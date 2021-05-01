#ifndef AUTHORIZERWINDOW_H
#define AUTHORIZERWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QListWidget>
#include <QAbstractListModel>
#include <QStackedWidget>

#include "include/community.h"

class IAuthorizerWindow {
public:
    virtual void drawForm() = 0;
    virtual bool sendMessage(MyMessage *message) = 0;
    virtual bool checkFromOnValid(User *user) = 0;
};

class AuthorizerWindow : public IAuthorizerWindow {
public:
    AuthorizerWindow(bool isValid = false): isValid(isValid) {}
    void drawForm() override {}
    bool sendMessage(MyMessage *message) override { return true; }
    bool checkFromOnValid(User *user) override { return true; }
private:
    bool isValid;
};

#endif // AUTHORIZERWINDOW_H

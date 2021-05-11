#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H
#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QListWidget>
#include <QAbstractListModel>
#include <QStackedWidget>

#include "include/community.h"

class ISettingsWindow {
public:
    virtual void drawUserSettings() = 0;
    virtual bool changeSettings() = 0;
    virtual bool saveSettings() = 0;
    virtual bool chooseUserPhoto() = 0;
};

class SettingsWindow : public QWidget, public ISettingsWindow {
    Q_OBJECT
public:
    SettingsWindow(QWidget * parent = nullptr, QStackedWidget * main = nullptr, User * user = nullptr);
    void drawUserSettings() override {}
    bool changeSettings() override { return true; }
    bool saveSettings() override { return true; }
    bool chooseUserPhoto() override { return true; }
private:
    QStackedWidget * main;
    User * user;
};

#endif // SETTINGSWINDOW_H

#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H
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
    SettingsWindow(QWidget * parent = nullptr, QStackedWidget * main = nullptr, std::shared_ptr<User> user = std::make_shared<User>());
    void addSettings(QString labelText, QString changeItem);
    void drawUserSettings() override {}
    bool changeSettings() override { return true; }
    bool saveSettings() override { return true; }
    bool chooseUserPhoto() override { return true; }

public slots:
    void backToMenu();
    void changeUserName();
private:
    QStackedWidget * main;
    std::shared_ptr<User> user;

    QVBoxLayout *settings;

    QLabel *userName;
    QLineEdit *changeName;
};

#endif // SETTINGSWINDOW_H

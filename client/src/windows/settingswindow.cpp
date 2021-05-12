#include "include/windows/settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent, QStackedWidget *main, User *user)
        :QWidget(parent), main(main), user(user)
{
    settings = new QVBoxLayout();

    MyButton * chooseThemeBtn = new MyButton("Choose theme");
    settings->addWidget(chooseThemeBtn);

    setLayout(settings);
}

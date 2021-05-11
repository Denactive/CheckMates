#include "include/windows/settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent, QStackedWidget *main, User *user)
        :QWidget(parent), main(main), user(user)
{

}

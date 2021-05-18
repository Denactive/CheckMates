#include "include/windows/settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent, QStackedWidget *main, std::shared_ptr<User> user)
        :QWidget(parent), main(main), user(user)
{
    settings = new QVBoxLayout();

    MyButton * chooseThemeBtn = new MyButton("Choose theme");
    settings->addWidget(chooseThemeBtn);

    MyButton * backBtn = new MyButton("BACK");
    connect(backBtn, SIGNAL(clicked()), this, SLOT(backToMenu()));
    settings->addWidget(backBtn);

    setLayout(settings);
}

void SettingsWindow::backToMenu()
{
    main->setCurrentIndex(0);
    qDebug() << "settings -> main\n";
}

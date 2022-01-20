#include "include/windows/settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent, QStackedWidget *main, std::shared_ptr<User> user)
        :QWidget(parent), main(main), user(user)
{
    settings = new QVBoxLayout();
    settings->setAlignment(Qt::AlignCenter);

    PhotoWidget *userPhoto = new PhotoWidget(user->getUserPhoto(), QSize(100,100));
    settings->addWidget(userPhoto);

    addSettings("Name: ", user->getName());
    addSettings("Login: ", user->getLogin());
    addSettings("Password: ", user->getUserPassword());

    MyButton * backBtn = new MyButton("BACK");
    connect(backBtn, SIGNAL(clicked()), this, SLOT(backToMenu()));
    settings->addWidget(backBtn);

    setLayout(settings);
}

void SettingsWindow::addSettings(QString labelText, QString changeItem)
{
    QHBoxLayout *nameSettings = new QHBoxLayout();
    userName = new QLabel(labelText);
    changeName = new QLineEdit(changeItem);
    MyButton * changeNameBtn = new MyButton("Change");
    connect(changeNameBtn, SIGNAL(clicked()), this, SLOT(changeUserName()));
    nameSettings->addWidget(userName);
    nameSettings->addWidget(changeName);
    nameSettings->addWidget(changeNameBtn);

    settings->addLayout(nameSettings);
}

void SettingsWindow::backToMenu()
{
    main->setCurrentIndex(0);
    qDebug() << "settings -> main\n";
}

void SettingsWindow::changeUserName()
{
    user->setName(changeName->text());
    userName->setText("Name: " + user->getName());
}

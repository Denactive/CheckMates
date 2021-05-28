#include <QDebug>
#include "include/windows/mainwindow.h"

MainWindow::MainWindow(std::shared_ptr<Database> db, QWidget * parent) :QWidget(parent), db(db) {
    setStyleSheet("background-image: url(../img/background2.jpg); background-color: #EDECEA;");
    main = new QStackedWidget();
    mainLayout = new QVBoxLayout();

    // get data from database
    usrsInfo = db->getUsersData(); // все пользователи для регистрации, получаем отсортированных по рейтингу
    frnsInfo = db->getUsersData(); // друзья регистрируемого игрока, должен заполниться после login, пока заглушка
    std::shared_ptr<GameInfo> gameInfo = db->getGameInfo();

    std::vector<std::shared_ptr<Chat>> chatsInfo = db->getChats();

    for (int i = 0; i < int(usrsInfo.size()); ++i) {
        std::shared_ptr<User> newUser = std::make_shared<User>(usrsInfo[i].name, usrsInfo[i].rating,
                         frnsInfo[i].password, usrsInfo[i].login, usrsInfo[i].photoPath);
        friendsInfo.push_back(newUser);
    }

    /*qDebug() << "chats" << chatsInfo.size();
    for (auto & value : chatsInfo) {
       std::vector<MyMessage> msgs = value->getMessages();
       if (!msgs.size()) qDebug() << "not messages in chat";

       for (auto & msg : msgs)
          qDebug() << msg.getMessage();
    }*/

    for (int i = 0; i < 5 && i < int(usrsInfo.size()); ++i) {
        std::shared_ptr<User> newUser = std::make_shared<User>(usrsInfo[i].name, usrsInfo[i].rating,
                                  usrsInfo[i].password, usrsInfo[i].login, usrsInfo[i].photoPath);

        topUsersInfo.push_back(newUser);
    }

    setRegisterUser(gameInfo->meId);
    opponent = friendsInfo[gameInfo->opponentId];
    // end of get data

    MenuWindow *menuWindow = new MenuWindow(this, main, false, chatsInfo, friendsInfo, gameInfo, opponent, friendsInfo);

    SettingsWindow *settingsWindow = new SettingsWindow(this, main, infoAboutMe);
    AuthorizerWindow *authorizerWindow = new AuthorizerWindow(this, main, true);

    main->insertWidget(0, menuWindow);

    main->insertWidget(2, settingsWindow);
    main->insertWidget(3, authorizerWindow);

    drawTop();
    //mainLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addWidget(main);
    drawBottom();

    setLayout(mainLayout);
    setWindowTitle("SaberChess");
}

MainWindow::~MainWindow()
{
    delete main;
}

void MainWindow::drawTop()
{
     QHBoxLayout *topLayout = new QHBoxLayout();

     QLabel * gameName = new QLabel("SaberChess");
     gameName->setStyleSheet("font-weight: bold; color: #464545; font-size:26px; font-family: 'LucidaGrande'; ");

     MyButton* community = createButton("Community", SLOT(communityClicked()));

     topUsers = new QComboBox(this);

     for (auto & userValue : topUsersInfo) {
         topUsers->addItem(userValue->getName(), Qt::TextAlignmentRole);
     }
     //connect(topUsers, SIGNAL(clicked()), this, SLOT(topPlayersClicked()));

     MyButton* settings = createButton("Settings", SLOT(settingsClicked()));

     topLayout->addWidget(gameName);
     topLayout->addWidget(community);
     topLayout->addWidget(topUsers);
     topLayout->addWidget(settings);

     authorizerIs = new QWidget();
     authorizerNo = new QWidget();

     // is authorizer
     QHBoxLayout * authorizeIsLayout = new QHBoxLayout();
     QVBoxLayout *settingsLayout = new QVBoxLayout();
     settingsLayout->setAlignment(Qt::AlignRight);

     PhotoWidget *userPhoto = new PhotoWidget(infoAboutMe->getUserPhoto(), QSize(50,50));
     settingsLayout->addWidget(userPhoto);
     settingsLayout->addWidget(new QLabel(infoAboutMe->getName()));

     MyButton* logout = createButton("Log out", SLOT(logoutClicked()));

     authorizeIsLayout->addLayout(settingsLayout);
     authorizeIsLayout->addWidget(logout);

     // no authorizer
     QHBoxLayout * authorizerContainer = new QHBoxLayout();

     MyButton* login = createButton("Log in", SLOT(loginClicked()));
     MyButton* reg = createButton("Register", SLOT(registrClicked()));
//     login->addStyle("height: " + QString::number(double(community->sizeHint().height())) + "px; ");
//     reg->addStyle("height: " + QString::number(double(community->sizeHint().height())) + "px; ");

     QLabel * margin = new QLabel();
     margin->setStyleSheet("width: 50px;");
     authorizerContainer->addWidget(margin);
     authorizerContainer->addWidget(login);
     authorizerContainer->addWidget(reg);

     authorizerIs->setLayout(authorizeIsLayout);
     authorizerNo->setLayout(authorizerContainer);

     topLayout->addWidget(authorizerIs);
     topLayout->addWidget(authorizerNo);

     if (!infoAboutMe)
         authorizerIs->hide();
     else
         authorizerNo->hide();

     // some design correct
     topUsers->setEditable(true);
     topUsers->lineEdit()->setReadOnly(true);
     topUsers->lineEdit()->setText("TOP PLAYERS");
     topUsers->lineEdit()->setAlignment(Qt::AlignCenter);
     topUsers->setStyleSheet("height: " + QString::number(community->sizeHint().height() + 30) + "; text-align:center; \
            background-color: #ACCCC4; border: 2px solid #464545; border-radius: 10%");

     mainLayout->addLayout(topLayout);
}

void MainWindow::drawBottom()
{
    QHBoxLayout *bottomLayout = new QHBoxLayout();

    MyButton* about = createButton("ABOUT GAME " + heart, SLOT(aboutClicked()));
    MyButton* developers = createButton("Developers", SLOT(developersClicked()));
    MyButton* donate = createButton("DONATE", SLOT(donateClicked()));
    MyButton* contacts = createButton("Contacts", SLOT(contactsClicked()));
    MyButton* exit = createButton("EXIT", SLOT(exitClicked()));

    bottomLayout->addWidget(about);
    bottomLayout->addWidget(developers);
    bottomLayout->addWidget(donate);
    bottomLayout->addWidget(contacts);
    bottomLayout->addWidget(exit);

    mainLayout->addLayout(bottomLayout);
}

void MainWindow::setRegisterUser(int index)
{
    if (usrsInfo.size() > 0) {
        infoAboutMe = std::make_shared<User>();
        infoAboutMe->setName(usrsInfo[index].name);
        infoAboutMe->setLogin(usrsInfo[index].login);
        infoAboutMe->setPassword(usrsInfo[index].password);
        infoAboutMe->setUserPhoto(usrsInfo[index].photoPath);
        infoAboutMe->changeRating(usrsInfo[index].rating);

        if (DEBUGDATA) qDebug() << "current user: " << infoAboutMe->getName();
    }
}

void MainWindow::onSearchChatClicked()
{
    QMessageBox::information(this, "Hello from friend", "Привет!");
}

void MainWindow::communityClicked()
{
    QMessageBox::information(this, "Community", "Здесь должен быть переход на страничку с командой, \
            её ачивками и списком других команд. Но это так, наши желания :)");
}

void MainWindow::settingsClicked()
{
    QMessageBox::information(this, "Настройки", "Переход на страничку с настройками");
    main->setCurrentIndex(2);
}

void MainWindow::aboutClicked()
{
    QMessageBox::information(this, "About", "Здесь будет инструкция как играть и инфа о приложении");
}

void MainWindow::developersClicked()
{
    QMessageBox::information(this, "Developers", "Developers: \n"\
                                                "Турчин Денис \n"\
                                                "Очеретная Светлана \n"\
                                                "Любский Юрий \n"\
                                                "Овчинникова Ксения");
}

void MainWindow::donateClicked()
{
    QMessageBox::information(this, "Donate", "Application created for educational purposes");
}

void MainWindow::contactsClicked()
{
    QMessageBox::information(this, "Contacts", "Если есть вопросы, пишите вк: \n"\
                                                "@denactive\n"\
                                                "@svetlanlka\n"\
                                                "@ylybskiy\n"\
                                                "@kseniaparvaty");
}

void MainWindow::exitClicked()
{
    this->close();
    //QApplication::quit();
}

void MainWindow::logoutClicked()
{
    QMessageBox::StandardButton reply =
            QMessageBox::question(this, "Logout", "Если вы действительно хотите выйти из аккаунта, нажмите ОК", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        infoAboutMe = nullptr;
        authorizerIs->hide();
        authorizerNo->show();
    }
}

void MainWindow::loginClicked()
{
    setRegisterUser(0);
    authorizerIs->show();
    authorizerNo->hide();
}

void MainWindow::registrClicked()
{
    setRegisterUser(0);
    authorizerIs->show();
    authorizerNo->hide();
}

MyButton *MainWindow::createButton(const QString &text, const char *member)
{
    MyButton *btn = new MyButton(text);
    connect(btn, SIGNAL(clicked()), this, member);
    return btn;
}

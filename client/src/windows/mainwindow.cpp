#include <QDebug>
#include "include/windows/mainwindow.h"

MainWindow::MainWindow(std::shared_ptr<Database> db, QWidget * parent) :QWidget(parent), db(db) {
    main = new QStackedWidget();
    mainLayout = new QVBoxLayout();

    GameWindow *gameWindow = new GameWindow(this, main);

    // get data from database
    std::vector<UserInfo> usrsInfo = db->getUsersData();
    std::vector<Chat*> chatsInfo = db->getChats();

    std::vector<User*> friendsInfo;
    for (int i = 0; i < int(usrsInfo.size()); ++i) {
        User *newUser = new User(usrsInfo[i].name, usrsInfo[i].rating,
                         usrsInfo[i].password, usrsInfo[i].login, usrsInfo[i].photoPath);
//        for (int j = 0; j < 5; ++j) {
//            MyMessage newMessage;
//            newMessage.changeMessage("chat " + QString::number(i) + " ,msg " + QString::number(j));
//            newChat->addMessage(newMessage);
//        }
//        chatInfo.push_back(&newChat);
        friendsInfo.push_back(newUser);
    }

    qDebug() << "chats" << chatsInfo.size();
    for (auto & value : chatsInfo) {
       std::vector<MyMessage> msgs = value->getMessages();
       if (!msgs.size()) qDebug() << "not messages in chat";

       for (auto & msg : msgs)
           qDebug() << msg.getMessage();
    }

    for (int i = 0; i < 5 && i < int(usrsInfo.size()); ++i) {
        User *newUser = new User(usrsInfo[i].name, usrsInfo[i].rating,
                                  usrsInfo[i].password, usrsInfo[i].login, usrsInfo[i].photoPath);

        topUsersInfo.push_back(newUser);
    }


    infoAboutMe = new User();
    infoAboutMe->setName(usrsInfo[0].name);
    infoAboutMe->setLogin(usrsInfo[0].login);
    infoAboutMe->setPassword(usrsInfo[0].password);
    infoAboutMe->setUserPhoto(usrsInfo[0].photoPath);
    infoAboutMe->changeRating(usrsInfo[0].rating);

    qDebug() << "current user: " << infoAboutMe->getName();
    // end of get data

    MenuWindow *menuWindow = new MenuWindow(this, main, false, chatsInfo, friendsInfo);

    qDebug() << "point";

    SettingsWindow *settingsWindow = new SettingsWindow(this, main, infoAboutMe);
    AuthorizerWindow *authorizerWindow = new AuthorizerWindow(this, main, true);

    main->insertWidget(0, menuWindow);
    main->insertWidget(1, gameWindow);
    main->insertWidget(2, settingsWindow);
    main->insertWidget(3, authorizerWindow);

    drawTop();
    //mainLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addWidget(main);
    drawBottom();

    setLayout(mainLayout);
    setWindowTitle("Main");
    setStyleSheet("background-color: lightblue;");
}

MainWindow::~MainWindow()
{
    delete main;
}

void MainWindow::drawTop()
{
     QHBoxLayout *topLayout = new QHBoxLayout();

     QLabel * gameName = new QLabel("SaberChess");
     gameName->setStyleSheet("font-weight: bold; color: darkblue; font-size:26px;");

     topUsers = new QComboBox(this);

     for (auto & userValue : topUsersInfo) {
         topUsers->addItem(userValue->getName(), Qt::TextAlignmentRole);
     }
     //connect(topUsers, SIGNAL(clicked()), this, SLOT(topPlayersClicked()));

     MyButton* community = createButton("Community", SLOT(communityClicked()));
     MyButton* settings = createButton("Settings", SLOT(settingsClicked()));

     topLayout->addWidget(gameName);
     topLayout->addWidget(topUsers);
     topLayout->addWidget(community);
     topLayout->addWidget(settings);

     if (infoAboutMe) {
        QHBoxLayout *settingsLayout = new QHBoxLayout();
        settingsLayout->setAlignment(Qt::AlignRight);

        settingsLayout->addWidget(new QLabel(infoAboutMe->getName()));
        PhotoWidget *userPhoto = new PhotoWidget(infoAboutMe->getUserPhoto(), QSize(50,50));
        settingsLayout->addWidget(userPhoto);

        topLayout->addLayout(settingsLayout);
     }

     // some design correct
     topUsers->setStyleSheet("height: " + QString::number(community->sizeHint().height()) + "; text-align:center;");
     topUsers->setEditable(true);
     topUsers->lineEdit()->setReadOnly(true);
     topUsers->lineEdit()->setText("TOP PLAYERS");
     topUsers->lineEdit()->setAlignment(Qt::AlignCenter);


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

MyButton *MainWindow::createButton(const QString &text, const char *member)
{
    MyButton *btn = new MyButton(text);
    connect(btn, SIGNAL(clicked()), this, member);
    return btn;
}

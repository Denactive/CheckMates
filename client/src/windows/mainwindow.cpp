#include <QKeyEvent>
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>
#include <QWidget>
#include <QGridLayout>
#include <QToolButton>
#include <QMessageBox>
#include <QApplication>

#include "include/windows/mainwindow.h"
#include "include/windows/gamewindow.h"
#include "include/windows/menuwindow.h"
#include "include/chessboard.h"
#include "include/gameobjects.h"

MainWindow::MainWindow(QWidget * parent) :QWidget(parent) {
    main = new QStackedWidget();
    mainLayout = new QVBoxLayout();

    GameWindow *gameWindow = new GameWindow(this, main);

    // initialization, structure from graphics class
    std::vector<Chat*> chatInfo; std::vector<User*> friendsInfo;
    for (int i = 0; i < 5; ++i) {
        User * newUser = new User("User " + QString::number(i));
        Chat * newChat = new Chat(newUser);
        for (int j = 0; j < 5; ++j) {
            MyMessage newMessage;
            newMessage.changeMessage("chat " + QString::number(i) + " ,msg " + QString::number(j));
            newChat->addMessage(newMessage);
        }
        chatInfo.push_back(newChat);
        friendsInfo.push_back(newUser);
    }
    for (int i = 0; i < 5; ++i) {
        int number = rand() % 10;
        User * newUser = new User("Top user " + QString::number(number));
        topUsersInfo.push_back(newUser);
    }
    infoAboutMe = new User();

    // end of zaglushka

    MenuWindow *mainWindow = new MenuWindow(this, main, false, chatInfo, friendsInfo);
    SettingsWindow *settingsWindow = new SettingsWindow();

    main->insertWidget(0, mainWindow);
    main->insertWidget(1, gameWindow);
    main->insertWidget(2, settingsWindow);

    drawTop();
    //mainLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addWidget(main);
    //mainLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
    drawBottom();

    setLayout(mainLayout);
    setWindowTitle("Main");
    setStyleSheet("background-color: lightblue;");
}

MainWindow::~MainWindow()
{
    /*for(int i = main->count(); i >= 0; i--)
    {
        QWidget* widget = main->widget(i);
        main->removeWidget(widget);
    }
    delete [] main;

    for(int i = 0; i < mainLayout->count(); ++i)
    {
        delete mainLayout->takeAt(i);
    }
    delete [] mainLayout;*/
    delete main;
}

void MainWindow::drawTop()
{
     QHBoxLayout *topLayout = new QHBoxLayout();

     QLabel * gameName = new QLabel("SaberChess");
     gameName->setStyleSheet("font-weight: bold; color: darkblue; font-size:26px;");

     topUsers = new QComboBox(this);

     for (size_t i = 0; i < topUsersInfo.size(); ++i) {
         topUsers->addItem(topUsersInfo[i]->getName(), Qt::TextAlignmentRole);
     }
     connect(topUsers, SIGNAL(clicked()), this, SLOT(topPlayersClicked()));
     //MyButton* topPlayers = createButton("TOP PLAYERS", SLOT(topPlayersClicked()));

     MyButton* community = createButton("Community", SLOT(communityClicked()));
     MyButton* settings = createButton("Settings", SLOT(settingsClicked()));

     topLayout->addWidget(gameName);
     topLayout->addWidget(topUsers);
     topLayout->addWidget(community);
     topLayout->addWidget(settings);

     // some design correct
     topUsers->setStyleSheet("height: " + QString::number(community->sizeHint().height()) + "; text-align:center;");
     topUsers->setEditable(true);
     topUsers->lineEdit()->setReadOnly(true);
     topUsers->lineEdit()->setText("TOP PLAYERS");
     topUsers->lineEdit()->setAlignment(Qt::AlignCenter);

     if (infoAboutMe) {
        PhotoWidget *userPhoto = new PhotoWidget(infoAboutMe->getUserPhoto(), QSize(50,50));
        topLayout->addWidget(userPhoto);
     }

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
    //mainLayout->addWidget(exit);
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

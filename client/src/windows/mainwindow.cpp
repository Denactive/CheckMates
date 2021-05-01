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

MainWindow::MainWindow() {
    main = new QStackedWidget();

    QVBoxLayout *mainLayout = new QVBoxLayout();

    QHBoxLayout *topLayout = new QHBoxLayout();
    QHBoxLayout *bottomLayout = new QHBoxLayout();

    GameWindow *game = new GameWindow(this, main);
    MenuWindow *mainWindow = new MenuWindow(this, main);

    main->insertWidget(0, mainWindow);
    main->insertWidget(1, game);

    MyButton* topPlayers = createButton("TOP PLAYERS", SLOT(topPlayersClicked()));
    MyButton* community = createButton("Community", SLOT(communityClicked()));
    MyButton* settings = createButton("Settings", SLOT(settingsClicked()));
    MyButton* about = createButton("ABOUT GAME", SLOT(aboutClicked()));
    MyButton* developers = createButton(heart, SLOT(developersClicked()));
    MyButton* donate = createButton("DONATE", SLOT(donateClicked()));
    MyButton* contacts = createButton("Contacts", SLOT(contactsClicked()));
    MyButton* exit = createButton("EXIT", SLOT(exitClicked()));

    topLayout->addWidget(topPlayers);
    topLayout->addWidget(community);
    topLayout->addWidget(settings);
    bottomLayout->addWidget(about);
    bottomLayout->addWidget(developers);
    bottomLayout->addWidget(donate);
    bottomLayout->addWidget(contacts);
    bottomLayout->addWidget(exit);

    mainLayout->addLayout(topLayout);
    mainLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addWidget(main);
    mainLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addLayout(bottomLayout);
    setLayout(mainLayout);
    setWindowTitle("Main");
    setStyleSheet("background-color: lightblue;");
}

bool MainWindow::eventListener(QObject *watched, QEvent *event)
{
//    if (event->type() == QEvent::KeyPress) {
//        if (watched == ui->playButton) {
//            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
//            if (keyEvent->key() == Qt::Key_Escape) {
////                ui->gameGroup->show();
//            }
//        }
//     }

//    QObject::eventFilter(watched, event);
    return true;
}

MainWindow::~MainWindow()
{
}

void MainWindow::onSearchChatClicked()
{
    QMessageBox::information(this, "Hello from friend", "Привет!");
}

void MainWindow::topPlayersClicked()
{

}

void MainWindow::communityClicked()
{

}

void MainWindow::settingsClicked()
{

}

void MainWindow::aboutClicked()
{

}

void MainWindow::developersClicked()
{

}

void MainWindow::donateClicked()
{

}

void MainWindow::contactsClicked()
{
    QMessageBox::information(this, "Contacts", "Developers: \n"\
                                                "Турчин Денис \n"\
                                                "Очеретная Светлана \n"\
                                                "Любский Юрий \n"\
                                                "Овчинникова Ксения");
}

void MainWindow::exitClicked()
{
    QApplication::quit();
}

MyButton *MainWindow::createButton(const QString &text, const char *member)
{
    MyButton *btn = new MyButton(text);
    connect(btn, SIGNAL(clicked()), this, member);
    return btn;
}

MyButton *App::createButton(const QString &text, const char *member)
{
    MyButton *btn = new MyButton(text);
    connect(btn, SIGNAL(clicked()), this, member);
    return btn;
}

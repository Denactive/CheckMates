#include <QLineEdit>
#include <QListWidget>
#include <QListView>
#include <QObject>
#include <QDebug>
#include <QMessageBox>

#include "include/windows/gamewindow.h"

void runGame();

GameWindow::GameWindow(QWidget *parent, QStackedWidget * main, std::shared_ptr<GameInfo> gameInfo,
                       std::shared_ptr<User> opponent, GlobalNet *globalNet)
    : QWidget(parent), gameInfo(gameInfo), opponent(opponent), main(main), globalNet(globalNet)
{
//    net::io_context ioc;
//    ioc.run();

//    std::unique_ptr<Client> client(new Client);

//    auto const port = 8000;
//    // auto const host = "25.40.253.246";
//    auto const host = "127.0.0.1";
//    auto const target = "/test.txt";

//    // QByteArray name;
//    // name.append("Sergey");
//    // client->post(host, port, target, name);

//    client->getData(host, port, target);
    // std::thread run(runGame);
    // runGame();
    // run.join();
    drawGame();
    //connect(this, SIGNAL(), this, SLOT(runGame()));
}

void GameWindow::drawGame()
{
    // qDebug() << "game opponent: " << opponent->getName();
    checkGame();

    game = new QVBoxLayout();

    drawGameTop();

    QHBoxLayout *middle = new QHBoxLayout();
    ChessBoard * board = new ChessBoard(main, gameInfo);

    middle->addWidget(board);
    middle->addWidget(drawGameChat());

    game->addLayout(middle);

    setStyleSheet("QListWidget::item { color: #464545; padding: 5px; background:  #E2DFD8; } ");

    setLayout(game);
}

void GameWindow::checkGame () {
    if (!gameInfo->isGame) {
        if (gameInfo->isVictory == 1) {
            QMessageBox::information(this, "Завершение игры", "Поздравляем, вы одержали победу!");
        } else if (gameInfo->isVictory == 2) {
            QMessageBox::information(this, "Завершение игры", "К сожалению, вы проиграли :(");
        } else {
            QMessageBox::information(this, "Завершение игры", "Игра завершилась с ничьей");
        }

        main->setCurrentIndex(0);
        qDebug() << "game -> main\n";
    }
}

QWidget* GameWindow::drawGameChat()
{
    QWidget *chatWidget = new QWidget();
    chatWidget->setStyleSheet("background: #E2DFD8; border-radius: 20%; border: 2px solid #464545;");

    QVBoxLayout *bottomLayout = new QVBoxLayout();

    bottomLayout->addLayout(drawChat());

    QHBoxLayout * buttons = new QHBoxLayout();

    MyButton * btnSend = new MyButton("Send \n message");
    connect(btnSend, SIGNAL(clicked()), this, SLOT(sendClicked()));
    buttons->addWidget(btnSend);

    MyButton * surrenderButton = new MyButton("Surrender");
    connect(surrenderButton, SIGNAL(clicked()), this, SLOT(surrender()));
    buttons->addWidget(surrenderButton);

    MyButton * offerDrawButton = new MyButton("Offer Draw");
    connect(offerDrawButton, SIGNAL(clicked()), this, SLOT(offerDraw()));
    buttons->addWidget(offerDrawButton);

    bottomLayout->addLayout(buttons);
    ///bottomLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    chatWidget->setLayout(bottomLayout);
    return chatWidget;
}

void GameWindow::drawGameTop()
{
    QHBoxLayout *topLayout = new QHBoxLayout();

    gameTime = new QLabel("Time: " + QTime::currentTime().toString("hh:mm:ss"));
    topLayout->addWidget(gameTime);
    QTimer * gameTimer = new QTimer();
    connect(gameTimer, SIGNAL(timeout), this, SLOT(slotTimerAlarm()));
    gameTimer->start(1000);

    topLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    gameMessage = new QLabel("");
    if (gameInfo->isCheck) gameMessage->setText("King under Mat!");
    gameMessage->setStyleSheet("color: lightred; font-size: bold; ");
    topLayout->addWidget(gameMessage);

    topLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    topLayout->addLayout(playerStatisticsDraw());
    topLayout->setAlignment(Qt::AlignRight);

    game->addLayout(topLayout);
}

QVBoxLayout *GameWindow::playerStatisticsDraw()
{
    QVBoxLayout * playerStatistics = new QVBoxLayout();

    QSize photoSize(50, 50);
    QPixmap photo = opponent->getUserPhoto().scaled(photoSize, Qt::KeepAspectRatio);
    QLabel * playerPhotoWidget = new QLabel();
    playerPhotoWidget->setPixmap(photo);
    playerStatistics->addWidget(playerPhotoWidget);

    int time = opponent->gameTime();
    QLabel * playerTime = new QLabel(opponent->getName() + "\nTime: " + QString::number(time));
    playerStatistics->addWidget(playerTime);

    return playerStatistics;
}

QVBoxLayout* GameWindow::drawChat(Chat *chat)  {
    QVBoxLayout *chatLayout = new QVBoxLayout();
    gameChat = new QListWidget();
    gameChat->setStyleSheet("background: #EDECEA; border-radius: 0%;");
    chatLayout->addWidget(gameChat);

    writeMessage = new QLineEdit;
    writeMessage->setVisible(true);
    writeMessage->setStyleSheet("background: #EDECEA; border: 2px solid #464545; height: 40px; padding-left: 20px;");
    chatLayout->addWidget(writeMessage);

    return chatLayout;
}

void GameWindow::sendClicked()
{
    qDebug() << "send: " << writeMessage->text();
    // qDebug() << "buffer: " << QString::fromLocal8Bit(connection->buffer().c_str());

    QListWidgetItem *item = new QListWidgetItem(writeMessage->text());
    QFont font("Helvetica [Cronyx]", 20);
    item->setFont(font);

    gameChat->addItem(item);
    gameChat->item(gameChat->count() - 1)->setTextAlignment(Qt::AlignRight);

    writeMessage->clear();
    connect(gameChat->model(), SIGNAL(rowsInserted(const QModelIndex &, int, int)), gameChat, SLOT(scrollToBottom()));
}

void GameWindow::slotTimerAlarm()
{
    gameTime->setText("Time: " + QTime::currentTime().toString("hh:mm:ss"));
}

void GameWindow::surrender()
{
    QMessageBox::StandardButton reply =
            QMessageBox::question(this, "Окончание игры", "Вы действительно хотите сдаться и покинуть игру?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        main->setCurrentIndex(0);
        qDebug() << "game -> main\n";
    } else {
        qDebug() << "Была совершена попытка сдаться";
    }
}

void GameWindow::offerDraw()
{
   QMessageBox::StandardButton reply = QMessageBox::question(this, "Окончание игры", "Была предложена ничья", QMessageBox::Yes | QMessageBox::No);
   if (reply == QMessageBox::Yes) {
       main->setCurrentIndex(0);
       qDebug() << "Оппонент принял предложение о ничье";
       qDebug() << "game -> main\n";
   } else {
       qDebug() << "Оппонент не согласен на ничью";
   }
}

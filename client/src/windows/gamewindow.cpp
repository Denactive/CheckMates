#include <QLineEdit>
#include <QListWidget>
#include <QListView>
#include <QObject>
#include <QDebug>
#include <QMessageBox>

#include "include/windows/gamewindow.h"

void runGame();

GameWindow::GameWindow(QWidget *parent, QStackedWidget * main, std::shared_ptr<GameInfo> gameInfo,
                       std::shared_ptr<User> opponent, GlobalNet *globalNet, std::shared_ptr<Database> db)
    : QWidget(parent), gameInfo(gameInfo), opponent(opponent), main(main), globalNet(globalNet), db(db)
{
    gameWidgets = make_shared<GameWidgets>();
    startGame = db->getStartGameInfo();
    drawGame();
}

void GameWindow::drawGame()
{
    // qDebug() << "game opponent: " << opponent->getName();
    checkGame();

    gameWidgets->game = new QVBoxLayout();

    drawGameTop();

    QHBoxLayout *middle = new QHBoxLayout();
    ChessBoard * board = new ChessBoard(main, gameInfo);

    middle->addWidget(board);
    middle->addWidget(drawGameChat());

    gameWidgets->game->addLayout(middle);

    setStyleSheet("QListWidget::item { color: #464545; padding: 5px; background:  #E2DFD8; } ");

    setLayout(gameWidgets->game);
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

    gameWidgets->gameTime = new QLabel("Time: " + QTime::currentTime().toString("hh:mm:ss"));
    topLayout->addWidget(gameWidgets->gameTime);
    QTimer * gameTimer = new QTimer();
    connect(gameTimer, SIGNAL(timeout), this, SLOT(slotTimerAlarm()));
    gameTimer->start(1000);

    topLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    gameWidgets->gameMessage = new QLabel("");
    if (gameInfo->isCheck) gameWidgets->gameMessage->setText("King under Mat!");
    gameWidgets->gameMessage->setStyleSheet("color: lightred; font-size: bold; ");
    topLayout->addWidget(gameWidgets->gameMessage);

    topLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    topLayout->addLayout(playerStatisticsDraw());
    topLayout->setAlignment(Qt::AlignRight);

    gameWidgets->game->addLayout(topLayout);
}

QVBoxLayout *GameWindow::playerStatisticsDraw()
{
    QVBoxLayout * playerStatistics = new QVBoxLayout();

    QSize photoSize(50, 50);
    QPixmap photo = /*opponent->getUserPhoto()*/ startGame->avatarOpponent.scaled(photoSize, Qt::KeepAspectRatio);
    QLabel * playerPhotoWidget = new QLabel();
    playerPhotoWidget->setPixmap(photo);
    playerStatistics->addWidget(playerPhotoWidget);

    int rating = startGame->ratingOpponent; // opponent->gameTime();
    QLabel * playerRating = new QLabel(/*opponent->getName()*/startGame->nameOpponent + "\nRating: " + QString::number(rating));
    playerStatistics->addWidget(playerRating);

    return playerStatistics;
}

QVBoxLayout* GameWindow::drawChat(Chat *chat)  {
    QVBoxLayout *chatLayout = new QVBoxLayout();
    gameWidgets->gameChat = new QListWidget();
    gameWidgets->gameChat->setStyleSheet("background: #EDECEA; border-radius: 0%;");
    chatLayout->addWidget(gameWidgets->gameChat);

    gameWidgets->writeMessage = new QLineEdit;
    gameWidgets->writeMessage->setVisible(true);
    gameWidgets->writeMessage->setStyleSheet("background: #EDECEA; border: 2px solid #464545; height: 40px; padding-left: 20px;");
    chatLayout->addWidget(gameWidgets->writeMessage);

    return chatLayout;
}

void GameWindow::sendClicked()
{
    qDebug() << "send: " << gameWidgets->writeMessage->text();
    // qDebug() << "buffer: " << QString::fromLocal8Bit(connection->buffer().c_str());

    QListWidgetItem *item = new QListWidgetItem(gameWidgets->writeMessage->text());
    QFont font("Helvetica [Cronyx]", 20);
    item->setFont(font);

    gameWidgets->gameChat->addItem(item);
    gameWidgets->gameChat->item(gameWidgets->gameChat->count() - 1)->setTextAlignment(Qt::AlignRight);

    gameWidgets->writeMessage->clear();
    connect(gameWidgets->gameChat->model(), SIGNAL(rowsInserted(const QModelIndex &, int, int)), gameWidgets->gameChat, SLOT(scrollToBottom()));
}

void GameWindow::slotTimerAlarm()
{
    gameWidgets->gameTime->setText("Time: " + QTime::currentTime().toString("hh:mm:ss"));
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

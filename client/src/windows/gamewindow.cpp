#include "include/windows/gamewindow.h"
#include "include/chessboard.h"
#include "include/gameobjects.h"
#include <QLineEdit>
#include <QListWidget>
#include <QListView>
#include <QObject>
#include <QDebug>
#include <QMessageBox>

GameWindow::GameWindow(QWidget *parent, QStackedWidget * main) : QWidget(parent), main(main)
{
    game = new QGridLayout();

    drawChessBoard();
    drawChat();
    drawSendButton();

    MyButton * surrenderButton = new MyButton("Surrender");
    connect(surrenderButton, SIGNAL(clicked()), this, SLOT(surrender()));
    game->addWidget(surrenderButton);

    MyButton * offerDrawButton = new MyButton("Offer Draw");
    connect(offerDrawButton, SIGNAL(clicked()), this, SLOT(offerDraw()));
    game->addWidget(offerDrawButton);

    setLayout(game);
}

void GameWindow::drawChessBoard() {
    ChessBoard *board = new ChessBoard();
    QHBoxLayout *boardLayout = new QHBoxLayout();
    boardLayout->setAlignment(Qt::AlignCenter);
    boardLayout->addWidget(board);

    game->addLayout(boardLayout, 0, 0, 1, 10);
}

void GameWindow::drawChat(Chat *chat)  {
    gameChat = new QListWidget();
    game->addWidget(gameChat, 1, 0, 1, 10);

    writeMessage = new QLineEdit;
    writeMessage->setVisible(true);
    game->addWidget(writeMessage, 2, 0, 1, 9);

    //    gameChat->addItem("message 1");
    //    gameChat->addItem("message 2");
    //    gameChat->addItem("message 3");
    //    gameChat->item(2)->setTextAlignment(Qt::AlignRight);
}

void GameWindow::drawSendButton(MyMessage *message)
{
    MyButton * btnSend = new MyButton("Send");
    connect(btnSend, SIGNAL(clicked()), this, SLOT(sendClicked()));
    game->addWidget(btnSend, 2, 9, 1, 1);
}

void GameWindow::sendClicked()
{
    qDebug() << "send: " << writeMessage->text();
    gameChat->addItem(writeMessage->text());
    gameChat->item(gameChat->count() - 1)->setTextAlignment(Qt::AlignRight);

    writeMessage->clear();
    connect(gameChat->model(), SIGNAL(rowsInserted(const QModelIndex &, int, int)), gameChat, SLOT(scrollToBottom()));
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
   QMessageBox::question(this, "Окончание игры", "Была предложена ничья. Допустим, игрок согласился", QMessageBox::Yes | QMessageBox::No);
   main->setCurrentIndex(0);
   qDebug() << "game -> main\n";
}

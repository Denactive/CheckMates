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
    QGridLayout *game = new QGridLayout();
    ChessBoard * board = new ChessBoard();
    QHBoxLayout *boardLayout = new QHBoxLayout();
    boardLayout->setAlignment(Qt::AlignCenter);
    boardLayout->addWidget(board);
    game->addLayout(boardLayout, 0, 0, 1, 10);


    QListWidget * gameChat = new QListWidget();
//    gameChat->addItem("message 1");
//    gameChat->addItem("message 2");
//    gameChat->addItem("message 3");

//    gameChat->item(2)->setTextAlignment(Qt::AlignRight);
    game->addWidget(gameChat, 1, 0, 1, 10);

    QLineEdit * writeMessage = new QLineEdit;
    writeMessage->setVisible(true);
    game->addWidget(writeMessage, 2, 0, 1, 9);

    //MyButton *btnSend = createButton("Отправить", SLOT(sendClicked()));

    //game->addWidget(btnSend, 2, 9, 1, 1);
    MyButton * surrenderButton = new MyButton("Surrender");
    connect(surrenderButton, SIGNAL(clicked()), this, SLOT(surrender()));
    game->addWidget(surrenderButton);

    MyButton * offerDrawButton = new MyButton("Offer Draw");
    connect(offerDrawButton, SIGNAL(clicked()), this, SLOT(offerDraw()));
    game->addWidget(offerDrawButton);

    setLayout(game);
}

void GameWindow::sendClicked()
{
    qDebug() << "send\n";
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

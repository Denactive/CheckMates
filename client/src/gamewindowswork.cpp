#include "../include/gamewindowswork.h"
#include <QLineEdit>
#include <QListWidget>
#include <QListView>
#include <QObject>
#include <QDebug>

Game::Game(QWidget *parent) : QWidget(parent)
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
    setLayout(game);
}

void Game::sendClicked()
{
    qDebug() << "send\n";
}

MyButton *Game::createButton(const QString &text, const char *member)
{
    MyButton *btn = new MyButton(text);
    connect(btn, SIGNAL(clicked()), this, member);
    return btn;
}

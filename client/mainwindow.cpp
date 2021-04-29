#include <QKeyEvent>
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>
#include <QWidget>
#include <QGridLayout>
#include <QToolButton>

#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "include/chessboard.h"

MainWindow::MainWindow()/*(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)*/
{
//    ui->setupUi(this);

//    ui->gameWindowWidget->hide();

//    QPixmap pix(":/img/userPhoto.png");
//    int width = ui->userPhoto->width() / 2;
//    int height = ui->userPhoto->height() / 2;
//    ui->userPhoto->setPixmap(pix.scaled(width, height, Qt::KeepAspectRatio));

    // practice
//    m_lineup = new QLineEdit();
//    m_linedown = new QLineEdit();
//    m_sign = new QLabel();
    QVBoxLayout *mainLayout = new QVBoxLayout();
    QHBoxLayout *topLayout = new QHBoxLayout();
    QHBoxLayout *bottomLayout = new QHBoxLayout();
    QGridLayout *gameLayout = new QGridLayout(); // to class Game
//   //mainLayout->setSizeConstraint(QLayout::SetFixedSize);

//    QFont font = m_lineup->font();
//    font.setPointSize(font.pointSize() + 8);

//    m_lineup->setFont(font);
//    m_lineup->setReadOnly(true);
//    m_lineup->setAlignment(Qt::AlignRight);
//    m_lineup->setMaxLength(15);
//    m_lineup->setText("Not pressed");

//    m_linedown->setFont(font);
//    m_linedown->setReadOnly(true);
//    m_linedown->setAlignment(Qt::AlignRight);
//    m_linedown->setMaxLength(15);

//    //    MyButton* m_cells[64];
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

    ChessBoard * board = new ChessBoard();
    gameLayout->addLayout(board, 0, 0);

    mainLayout->addLayout(topLayout);
    mainLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addLayout(gameLayout);
    mainLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
    mainLayout->addLayout(bottomLayout);
    setLayout(mainLayout);
    setWindowTitle("Main");
    // qApp->installEventFilter(this);
}

bool MainWindow::eventListener(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        if (watched == ui->playButton) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Escape) {
//                ui->gameGroup->show();
            }
        }
     }

    QObject::eventFilter(watched, event);
    return true;
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_playButton_clicked()
{
    ui->gameWindowWidget->show();
    ui->centerWidget->hide();
}

void MainWindow::on_pushButton_clicked()
{
    QMessageBox::StandardButton reply =
            QMessageBox::question(this, "Окончание игры", "Вы действительно хотите сдаться и покинуть игру?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        ui->gameWindowWidget->hide();
        ui->centerWidget->show();
    } else {
        qDebug() << "Была совершена попытка сдаться";
    }
}

void MainWindow::on_QuitButton_clicked()
{
    QApplication::quit();
}

void MainWindow::on_searchChatButton_clicked()
{
    QString message = ui->searchChatLine->text();

    if (message == "hello") {
        QMessageBox::information(this, "Hello from friend", "Привет!");
    }

    ui->searchChatLine->setText("Message send");
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

}

void MainWindow::exitClicked()
{

}

MyButton *MainWindow::createButton(const QString &text, const char *member)
{
    MyButton *btn = new MyButton(text);
    connect(btn, SIGNAL(clicked()), this, member);
    return btn;
}

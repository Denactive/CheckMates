#include "../include/graphics.h"
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/img/userPhoto.png");
    int width = ui->userPhoto->width();
    int height = ui->userPhoto->height();
    ui->userPhoto->setPixmap(pix.scaled(width, height, Qt::KeepAspectRatio));
}

void MainWindow::pushBoard()
{
//     QString contentPath;

//   #ifdef QT_DEBUG
//     contentPath = "../home/svetlana/tp/qtChess";
//   #else
//     contentPath = QApplicatsion::applicationDirPath();
//   #endif

//     setFocusPolicy(Qt::StrongFocus);

//     setSource(QUrl::fromLocalFile(contentPath + "/main.qml"));
//    QGridLayout *grid = new QGridLayout;
//    ChessBoard *chessboard = new ChessBoard;

//    ui->centralWidget->setLayout(chessboard);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_buttonSend_clicked()
{
    ui->sendMessage->setText("Message send");
    QString message = ui->textMessage->toPlainText();

    if (message == "Hello") {
        QMessageBox::information(this, "Hello from friend", "Привет!");
    }
}

void MainWindow::on_surrender_clicked()
{
//    QMessageBox::critical(this, "Error", "Error message");
    QMessageBox::StandardButton reply =
            QMessageBox::question(this, "Окончание игры", "Вы действительно хотите сдаться?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    } else {
        qDebug() << "Была совершена попытка сдаться";
    }
}

void MainWindow::on_quit_clicked()
{
    hide();
}

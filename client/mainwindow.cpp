#include <QKeyEvent>
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->gameWindowWidget->hide();

//    QPixmap pix(":/img/userPhoto.png");
//    int width = ui->userPhoto->width() / 2;
//    int height = ui->userPhoto->height() / 2;
//    ui->userPhoto->setPixmap(pix.scaled(width, height, Qt::KeepAspectRatio));

    qApp->installEventFilter(this);
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

#include "include/windows/mainwindow.h"

#include <QApplication>
#include <QWidget>
#include <QGridLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Database *chessDb = new Database();
    std::shared_ptr<Database> db(chessDb);
    MainWindow w(db);
    w.show();

    return a.exec();
}

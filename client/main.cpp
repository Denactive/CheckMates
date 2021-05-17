#include "include/windows/mainwindow.h"

#include <QApplication>
#include <QWidget>
#include <QGridLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::shared_ptr<Database> db = std::make_shared<Database>();
    MainWindow w(db);
    w.show();

    return a.exec();
}

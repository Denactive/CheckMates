#include "include/windows/mainwindow.h"

#include <QApplication>
#include <QWidget>
#include <QGridLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //App ap;
    //ap.show();
    //a.quit();
    //QApplication::quit();
    return a.exec();
}

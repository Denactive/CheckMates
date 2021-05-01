#include "mainwindow.h"

#include <QApplication>
#include <QWidget>
#include <QGridLayout>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.show();
    App ap;
    ap.show();
    return a.exec();
}

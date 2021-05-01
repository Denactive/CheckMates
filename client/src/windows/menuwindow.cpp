#include "include/windows/menuwindow.h"
#include "include/gameobjects.h"
#include <QLineEdit>
#include <QListWidget>
#include <QListView>
#include <QObject>
#include <QDebug>
#include <QMessageBox>

MenuWindow::MenuWindow(QWidget *parent, QStackedWidget *main, bool isMatching) :QWidget(parent), main(main), isMatching(isMatching)
{
    QGridLayout *mainGrid = new QGridLayout();
    MyButton * playButton = new MyButton("PLAY");
    connect(playButton, SIGNAL(clicked()), this, SLOT(tapPlay()));
    mainGrid->addWidget(playButton);
    setLayout(mainGrid);
}

void MenuWindow::tapPlay()
{
    main->setCurrentIndex(1);
    qDebug() << "main -> play\n";
}

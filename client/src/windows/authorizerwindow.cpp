#include "include/windows/authorizerwindow.h"

AuthorizerWindow::AuthorizerWindow(QWidget *parent, QStackedWidget *main, bool isValid)
    :QWidget(parent), main(main), isValid(isValid)
{
    authorizerMenu = new QVBoxLayout();

    MyButton * backBtn = new MyButton("BACK");
    connect(backBtn, SIGNAL(clicked()), this, SLOT(backToMenu()));
    authorizerMenu->addWidget(backBtn);

    setLayout(authorizerMenu);
}

void AuthorizerWindow::backToMenu()
{
    main->setCurrentIndex(0);
    qDebug() << "authorizer -> main\n";
}

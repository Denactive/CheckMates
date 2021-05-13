#include "include/windows/chatwindow.h"

ChatWindow::ChatWindow(QWidget *parent, QStackedWidget *main, Chat *chat)
        :QWidget(parent), main(main), chat(chat)
{
    chatMenu = new QVBoxLayout();

    MyButton * backBtn = new MyButton("BACK");
    connect(backBtn, SIGNAL(clicked()), this, SLOT(backToMenu()));
    chatMenu->addWidget(backBtn);

    setLayout(chatMenu);
}

void ChatWindow::backToMenu()
{
    main->setCurrentIndex(0);
    qDebug() << "chat -> main\n";
}


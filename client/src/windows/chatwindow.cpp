#include <QDebug>

#include "include/windows/chatwindow.h"

ChatWindow::ChatWindow(QWidget *parent, QStackedWidget *main, std::shared_ptr<Chat> chat)
        :QWidget(parent), main(main), chat(chat)
{
    chatMenu = new QVBoxLayout();

    MyButton * backBtn = new MyButton("BACK");
    connect(backBtn, SIGNAL(clicked()), this, SLOT(backToMenu()));
    chatMenu->addWidget(backBtn);

    if (!chat) {
        qDebug() << "chat nullptr";
    } else {
        qDebug() << "last msg: " << chat->getLastMessage().getMessage();
    }
    setLayout(chatMenu);
}

void ChatWindow::backToMenu()
{
    main->setCurrentIndex(0);
    qDebug() << "chat -> main\n";
}

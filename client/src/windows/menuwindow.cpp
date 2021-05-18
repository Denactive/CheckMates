﻿#include "include/windows/menuwindow.h"
#include "include/gameobjects.h"
#include <QLineEdit>
#include <QListWidget>
#include <QListView>
#include <QObject>
#include <QDebug>
#include <QMessageBox>

MenuWindow::MenuWindow(QWidget *parent, QStackedWidget *main, bool isMatching, std::vector<std::shared_ptr<Chat>> chatInfo, std::vector<std::shared_ptr<User>> friendsInfo)
    :QWidget(parent), main(main), isMatching(isMatching)
{
    menu = new QHBoxLayout();
    menu->setAlignment(Qt::AlignCenter);

    drawChats(chatInfo);
    //menu->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    drawMiddle();
    //menu->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    drawFriends(friendsInfo);

    setLayout(menu);

    copy(chatInfo.begin(), chatInfo.end(), back_inserter(this->chatInfo));
    if (DEBUG) qDebug() << "chat info: " << this->chatInfo[0]->getLastMessage().getMessage();
}

void MenuWindow::drawChats(std::vector<std::shared_ptr<Chat>> chatInfo) {
    //QWidget *chatsLayoutWidget = new QWidget();
    QVBoxLayout *chatsLayout = new QVBoxLayout();


    QLabel *chatHeader = new QLabel("Chats");
    chatHeader->setStyleSheet("color: darkred; font-size: 24px; font-weight: bold;");
    chatsLayout->addWidget(chatHeader);

    QHBoxLayout * searchLayout = new QHBoxLayout();
    searchChatLine = new QLineEdit();
    searchLayout->addWidget(searchChatLine);

    QToolButton * searchChatBtn = new QToolButton();
    searchChatBtn->setText("SEARCH");
    connect(searchChatBtn, SIGNAL(clicked()), this, SLOT(searchChat()));
    searchLayout->addWidget(searchChatBtn);

    searchChatBtn->setStyleSheet("height: " + QString::number(searchChatLine->sizeHint().height()) + ";");

    chatsLayout->addLayout(searchLayout);

    for (size_t i = 0; i < chatInfo.size(); ++i) {
        addChat(i, chatInfo);
    }

    for (auto & chatValue : chats) {
        chatsLayout->addWidget(chatValue);
    }

    //chatsLayoutWidget->setLayout(chatsLayout);
    //menu->addWidget(chatsLayoutWidget);
    menu->addLayout(chatsLayout);
}

void MenuWindow::drawMiddle()
{
    QWidget *middleLayoutWidget = new QWidget();

    QVBoxLayout *middleLayout = new QVBoxLayout();
    middleLayout->setAlignment(Qt::AlignCenter);

    QSizePolicy spRight(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spRight.setHorizontalStretch(2);
    middleLayoutWidget->setSizePolicy(spRight);

    middleLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));

    playButton = new MyButton("PLAY");
    connect(playButton, SIGNAL(clicked()), this, SLOT(tapPlay()));
    middleLayout->addWidget(playButton);

    isMatchingBox = new QCheckBox(" choose to search random player for play");
    middleLayout->addWidget(isMatchingBox);

    //previewLabelImage = new QLabel();
    //previewLabelImage->setScaledContents(true);
    previewLabelImage = new LabelImage();
    previewLabelImage->setAlignment(Qt::AlignCenter);
//    previewLabelImage->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored));
    QPixmap photo;
    if (photo.load("../img/preview.jpg")) {
        QSize photoSize(playButton->width(), playButton->height());
        QPixmap preview = photo.scaled(photoSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        previewLabelImage->setPixmap(preview);
        if (DEBUG) qDebug() << "file preview set";
    }
    else {
      previewLabelImage->setText(QString::fromLatin1("Sorry. Cannot find file for preview photo."));
      if (DEBUG) qDebug() << "file preview not found";
    }


    middleLayout->addWidget(previewLabelImage);
    middleLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));

    middleLayoutWidget->setLayout(middleLayout);
    menu->addWidget(middleLayoutWidget);
}


void MenuWindow::resizeEvent(QResizeEvent *event)
{

//    QPixmap photo("../img/preview.jpg");
//    previewPhotoWidget->resize(event->size().width(), double(event->size().width()) * double(photo.width() / photo.height()));
//    QSize photoSize(previewLabelImage->width(), previewLabelImage->height());
    if (DEBUG) qDebug() << "event size" << event->size().width() <<  " " << event->size().height();
    if (DEBUG) qDebug() << "preview size label" << previewLabelImage->getSize().width() <<  " " << previewLabelImage->getSize().height();
//    QPixmap preview = previewLabelImage->pixmap()->scaled(photoSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
////    preview.scaledToWidth(playButton->width());
//    previewLabelImage->setPixmap(preview);
//    previewPhotoWidget->setStyleSheet("border-image: url(../img/preview.jpg) cover");
    //previewLabelImage->resizeLabel(event);
}


void MenuWindow::drawFriends(std::vector<std::shared_ptr<User>> friendsInfo) {
    QVBoxLayout *friendsLayout = new QVBoxLayout();

    QLabel *friendHeader = new QLabel("Friends");
    friendHeader->setStyleSheet("color: darkred; font-size: 24px; font-weight: bold;");
    friendsLayout->addWidget(friendHeader);

    QHBoxLayout * searchLayout = new QHBoxLayout();
    searchFriendLine = new QLineEdit();
    searchLayout->addWidget(searchFriendLine);

    QToolButton * searchFriendBtn = new QToolButton();
    searchFriendBtn->setText("SEARCH");
    connect(searchFriendBtn, SIGNAL(clicked()), this, SLOT(searchFriend()));
    searchLayout->addWidget(searchFriendBtn);

    searchFriendBtn->setStyleSheet("height: " + QString::number(searchFriendLine->sizeHint().height()) + ";");
    searchFriendBtn->resize(searchFriendBtn->width(), searchFriendLine->sizeHint().height());


    friendsLayout->addLayout(searchLayout);

    if (DEBUG) qDebug() << "f size: " << friendsInfo.size();

    for (size_t i = 0; i < friendsInfo.size(); ++i) {
        addFriend(i, friendsInfo);
    }

    for (auto & friendValue : friends) {
        friendsLayout->addWidget(friendValue);
    }

    menu->addLayout(friendsLayout);
}

void MenuWindow::tapPlay()
{
    if (!choosenFriend->isChecked() && !isMatchingBox->isChecked()) {
        QMessageBox::warning(this, "Not player to play", "Yot don't want to play with random player and you don't choose friend");
    } else {
        main->setCurrentIndex(1);
        qDebug() << "main -> play\n";
    }
}

void MenuWindow::chooseFriend()
{
    QCheckBox * clickFriend = (QCheckBox*) sender();
    if (clickFriend != choosenFriend) {
        choosenFriend->setChecked(false);
        clickFriend->setChecked(true);
        choosenFriend = clickFriend;
    } else {
        choosenFriend->setChecked(choosenFriend->isChecked());
    }
}

void MenuWindow::chooseChat()
{
    qDebug() << "menu -> chat";
    ChatButton *btn = (ChatButton*) sender();

    ChatWindow *chatWindow = new ChatWindow(this, main, btn->getChat());
    main->insertWidget(4, chatWindow);
    main->setCurrentIndex(4);
}

void MenuWindow::changeMatching()
{
    isMatchingBox->setChecked(isMatchingBox->isChecked());
}

void MenuWindow::addFriend(size_t index, std::vector<std::shared_ptr<User>> friendsInfo)
{
    QFrame *newFriend = new QFrame();
    newFriend->setFrameStyle(QFrame::Panel);
    newFriend->setFrameShadow(QFrame::Raised);
    newFriend->setLineWidth(2);

    QHBoxLayout *friendLayout = new QHBoxLayout();

    std::shared_ptr<User> user = friendsInfo[index];
    QLabel *userPhotoContainer = new QLabel("User photo");
    QSize sizePhoto(50, 50);
    QPixmap userPhoto = user->getUserPhoto().scaled(sizePhoto);
    userPhotoContainer->setPixmap(userPhoto);

    MyMessage fName = user->getName();
    QLabel *friendName = new QLabel(fName.getMessage());

    QCheckBox *friendCheckBox = new QCheckBox("");
    if (index == 0) {
        friendCheckBox->setCheckState(Qt::CheckState::Checked);
        choosenFriend = friendCheckBox;
    }
    connect(friendCheckBox, SIGNAL(clicked()), this, SLOT(chooseFriend()));

    friendLayout->addWidget(userPhotoContainer);
    friendLayout->addWidget(friendName);
    friendLayout->addWidget(friendCheckBox);

    newFriend->setLayout(friendLayout);
    friends.push_back(newFriend);
}

void MenuWindow::addChat(size_t index, std::vector<std::shared_ptr<Chat>> chatInfo)
{
    ChatButton *chat = new ChatButton();

    QHBoxLayout *chatLayout = new QHBoxLayout();

    //User * user = chatInfo[index]->getUser();
    QLabel *userPhotoContainer = new QLabel("User photo");
    QSize sizePhoto(50, 50);
    //QPixmap userPhoto("../img/userPhoto.png"); //user->getUserPhoto().scaled(sizePhoto);
    //userPhoto = userPhoto.scaled(sizePhoto);
    QPixmap userPhoto(chatInfo[index]->getUser()->getUserPhoto().scaled(sizePhoto));
    userPhotoContainer->setPixmap(userPhoto);


    MyMessage msg = chatInfo[index]->getLastMessage();

    QLabel *lastMessage = new QLabel(msg.getMessage());

    chatLayout->addWidget(userPhotoContainer);
    chatLayout->addWidget(lastMessage);

    chat->setLayout(chatLayout);



    chats.push_back(chat);
    chat->setChat(chatInfo[index]);
    connect(chats[index], SIGNAL(clicked()), this, SLOT(chooseChat()));
}

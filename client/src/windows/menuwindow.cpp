#include "include/windows/menuwindow.h"
#include "include/gameobjects.h"
#include <QLineEdit>
#include <QListWidget>
#include <QListView>
#include <QObject>
#include <QDebug>
#include <QMessageBox>

MenuWindow::MenuWindow(QWidget *parent, QStackedWidget *main, bool isMatching, std::vector<Chat*> chatInfo, std::vector<User*> friendsInfo)
    :QWidget(parent), main(main), isMatching(isMatching)
{
    menu = new QHBoxLayout();
    menu->setAlignment(Qt::AlignCenter);

    drawChats(chatInfo);
    menu->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    drawMiddle();
    menu->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    drawFriends(friendsInfo);

    setLayout(menu);
}

void MenuWindow::drawChats(std::vector<Chat*> chatInfo) {
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

    for (size_t i = 0; i < chatInfo.size(); ++i) {
        chatsLayout->addWidget(chats[i]);
    }

    menu->addLayout(chatsLayout);
}

void MenuWindow::drawMiddle()
{
    QVBoxLayout *middleLayout = new QVBoxLayout();
    middleLayout->setAlignment(Qt::AlignCenter);

    middleLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));

    MyButton * playButton = new MyButton("PLAY");
    connect(playButton, SIGNAL(clicked()), this, SLOT(tapPlay()));
    middleLayout->addWidget(playButton);

    isMatchingBox = new QCheckBox(" choose to search random player for play");
    //connect(isMatchingBox, SIGNAL(clicked()), this, SLOT(changeMatching()));
    middleLayout->addWidget(isMatchingBox);

    QPixmap photo("../img/preview.jpg");
    QSize photoSize(playButton->width(), playButton->height());

    QLabel * previewPhotoWidget = new QLabel();
    //previewPhotoWidget->setStyleSheet("border: url(../img/preview.jpg)");

    //int w = std::min(photo.width(), previewPhotoWidget->width());//previewPhotoWidget->maximumWidth());
    //int h = std::min(photo.height(), previewPhotoWidget->height());//previewPhotoWidget->maximumHeight());
    QPixmap preview = photo.scaled(photoSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    previewPhotoWidget->setPixmap(preview);
   //previewPhotoWidget->setScaledContents(true);
   //previewPhotoWidget->setSizePolicy(QSizePolicy::Fixed);

    middleLayout->addWidget(previewPhotoWidget);

    middleLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));

    menu->addLayout(middleLayout);
}

void MenuWindow::drawFriends(std::vector<User*> friendsInfo) {
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

    qDebug() << "f size: " << friendsInfo.size();

    for (size_t i = 0; i < friendsInfo.size(); ++i) {
        addFriend(i, friendsInfo);
    }

    for (size_t i = 0; i < friendsInfo.size(); ++i) {
        friendsLayout->addWidget(friends[i]);
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
    //QFrame * clickChat = (QFrame*) sender();
}

void MenuWindow::changeMatching()
{
    isMatchingBox->setChecked(isMatchingBox->isChecked());
}

void MenuWindow::addFriend(size_t index, std::vector<User*> friendsInfo)
{
    QFrame *newFriend = new QFrame();
    newFriend->setFrameStyle(QFrame::Panel);
    newFriend->setFrameShadow(QFrame::Raised);
    newFriend->setLineWidth(2);

    QHBoxLayout *friendLayout = new QHBoxLayout();

    User * user = friendsInfo[index];
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

void MenuWindow::addChat(size_t index, std::vector<Chat *> chatInfo)
{
    QFrame *chat = new QFrame();
    chat->setFrameStyle(QFrame::Panel);
    chat->setFrameShadow(QFrame::Raised);
    chat->setLineWidth(2);

    QHBoxLayout *chatLayout = new QHBoxLayout();

    User * user = chatInfo[index]->getUser();
    QLabel *userPhotoContainer = new QLabel("User photo");
    QSize sizePhoto(50, 50);
    QPixmap userPhoto = user->getUserPhoto().scaled(sizePhoto);
    userPhotoContainer->setPixmap(userPhoto);

    MyMessage msg = chatInfo[index]->getLastMessage();
    QLabel *lastMessage = new QLabel(msg.getMessage());

    chatLayout->addWidget(userPhotoContainer);
    chatLayout->addWidget(lastMessage);

    chat->setLayout(chatLayout);
    connect(chat, SIGNAL(clicked()), this, SLOT(chooseChat()));
    chats.push_back(chat);
}

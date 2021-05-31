#include "include/windows/menuwindow.h"
#include "include/gameobjects.h"
#include <QLineEdit>
#include <QListWidget>
#include <QListView>
#include <QObject>
#include <QDebug>
#include <QMessageBox>

MenuWindow::MenuWindow(QWidget * parent, QStackedWidget * main, bool isMatching,
                                  std::vector<std::shared_ptr<Chat>> chatInfo, std::vector<std::shared_ptr<User>> friendsInfo,
                                  std::shared_ptr<GameInfo> gameInfo,  std::shared_ptr<User> opponent, std::vector<std::shared_ptr<User>> frnsInfo,
                                  GlobalNet *globalNet, std::shared_ptr<std::string> token)
    :QWidget(parent), main(main), isMatching(isMatching), gameInfo(gameInfo), friendsInfo(frnsInfo), opponent(opponent), globalNet(globalNet), token_(token)
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

    for (int i = 0; i < 5; ++i) {
        if (i < chats.size()) chatsLayout->addWidget(chats[i]);
        else chatsLayout->addWidget(new QWidget());
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
        previewLabelImage->setStyleSheet("border: 2px solid #464545; border-radius: 10%;");
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

    for (size_t i = 0; i < friendsInfo.size() || i < 5; ++i) {
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
        if (DEBUG) qDebug() << "game info opponent id: " << gameInfo->opponentId;
        if (DEBUG) qDebug() << "opponent: " << opponent->getName();
        //---------------- [qt connection]---------------
           auto const h_port = 8000;
           auto const h_host = "127.0.0.1";

           std::cout << "token id after begin game:" << *(token_);
           qDebug() << "token after begin game: " << QString::fromLocal8Bit(token_->c_str());
           std::string _target = "/start_game/" + *(token_);
           auto const h_target = _target.c_str();

           globalNet->httpClient->getData(h_host, h_port, h_target);
           // globalNet->httpClient->_download(globalNet->httpClient->setUrl(h_host, h_port, h_target));
        //-----------------------[end qt connection]---------------

           sleep(3);
           beginGame();
           // connect(&globalNet->httpClient->getManager(), SIGNAL(&globalNet->httpClient->getManager()::finished), this, SLOT(beginGame()));
    }
}

void MenuWindow::beginGame() {
    GameWindow *gameWindow = new GameWindow(this, main, gameInfo, opponent, globalNet);
    main->insertWidget(1, gameWindow);
    main->setCurrentIndex(1);
    qDebug() << "main -> play\n";
}

void MenuWindow::chooseFriend()
{
    CheckBoxUser * clickFriend = (CheckBoxUser*) sender();
    if (clickFriend != choosenFriend) {
        choosenFriend->setChecked(false);
        clickFriend->setChecked(true);
        choosenFriend = clickFriend;

        gameInfo->opponentId = clickFriend->getIndex();
    } else {
        choosenFriend->setChecked(choosenFriend->isChecked());
    }

    opponent = friendsInfo[gameInfo->opponentId];
}
void MenuWindow::chooseChat()
{
    qDebug() << "menu -> chat";
    FrameButton *btn = (FrameButton*) sender();

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
    FrameButton *newFriend = new FrameButton();

    QHBoxLayout *friendLayout = new QHBoxLayout();

    std::shared_ptr<User> user = friendsInfo[index];
    QLabel *userPhotoContainer = new QLabel("User photo");
    QSize sizePhoto(50, 50);
    QPixmap userPhoto = user->getUserPhoto().scaled(sizePhoto);
    userPhotoContainer->setPixmap(userPhoto);

    MyMessage fName = user->getName();
    QLabel *friendName = new QLabel(fName.getMessage());

    CheckBoxUser *friendCheckBox = new CheckBoxUser(this, int(index));
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
    FrameButton *chat = new FrameButton();

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

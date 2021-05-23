#include "include/database.h"
#include <QDebug>

Database::Database()
{
    QSqlDatabase bd;
    bd = QSqlDatabase::addDatabase("QSQLITE");
    bd.setDatabaseName("../database.db3");
    //QSqlDatabase::addDatabase("QSQLITE");
    bd.open();

    if (!bd.isOpen())
        qDebug() << "database not open";

    gameInfo = make_shared<GameInfo>();

    setGameInfoFromQuery();
    setUserDataFromQuery();
    fillChats();
}

void Database::setUserDataFromQuery()
{
    QSqlQuery query = QSqlQuery(this->database());
    if (!query.exec("SELECT _id, name, login, password, photoPath, rating FROM Users")) {
        qDebug() << query.lastError().databaseText();
        qDebug() << query.lastError().driverText();
    }

    while (query.next())
    {
        UserInfo newUsrInfo;
        QString name = query.value(1).toString();
        QString login = query.value(2).toString();
        QString password = query.value(3).toString();
        QString photoPath = query.value(4).toString();
        int rating = query.value(5).toInt();

        newUsrInfo.name = name;
        newUsrInfo.login = login;
        newUsrInfo.password = password;
        newUsrInfo.photoPath = photoPath;
        newUsrInfo.rating = rating;

        usrInfo.push_back(newUsrInfo);
    }
}

void Database::fillChats()
{
    QSqlQuery query = QSqlQuery(this->database());
    if (!query.exec("SELECT _id, text, chatID, fromWho FROM Messages ORDER BY chatID")) {
        qDebug() << query.lastError().databaseText();
        qDebug() << query.lastError().driverText();
    }


    int fillChatID = 0;
    int chatID = -1;
    while (true)
    {
        std::shared_ptr<Chat> newChat = std::make_shared<Chat>();
        if (chatID == -1)
            if (!query.next()) break;
        // qDebug() << "chatID" << chatID;
        while (chatID <= fillChatID) {
            chatID = query.value(2).toInt();
            QString text = query.value(1).toString();
            // qDebug() << "add: " << text;

            bool fromWho = query.value(3).toBool();
            MyMessage msg(text, fromWho);
            newChat->addMessage(msg);

            // qDebug() << "new chatID" << chatID;
            if (!query.next()) break;
        }
        fillChatID = chatID;
        chatsInfo.push_back(newChat);

        if (!query.isValid()) break;
    }

    QSqlQuery query2 = QSqlQuery(this->database());
    if (!query.exec("SELECT _id, UserID FROM Chats")) {
        qDebug() << query.lastError().databaseText();
        qDebug() << query.lastError().driverText();
    }

    while (query2.next()) {
        int id = query.value(0).toInt();
        int userId = query.value(1).toInt();

        chatsInfo[id]->setUser(findUser(userId));
    }
}

std::shared_ptr<User> Database::findUser(int index)
{
    QSqlQuery query = QSqlQuery(this->database());
    if (!query.exec("SELECT _id, UserID, MessagesID FROM Users WHERE _id=" + QString::number(index))) {
        qDebug() << query.lastError().databaseText();
        qDebug() << query.lastError().driverText();
    }
    std::shared_ptr<User> usr = std::make_shared<User>();

    return usr;
}

void Database::setGameInfoFromQuery()
{
    QSqlQuery query = QSqlQuery(this->database());
    if (!query.exec("SELECT _id, isVictory, currentPlayer, isCheck, isGame, newFigurePos, lastFigurePos, meID, opponentID from GameInfo" )) {
        qDebug() << query.lastError().databaseText();
        qDebug() << query.lastError().driverText();
    }
    std::shared_ptr<User> usr = std::make_shared<User>();


    gameInfo->meId = 0;
    gameInfo->opponentId = 1;
    gameInfo->currentPlayer = true;
    gameInfo->isCheck = false;
    gameInfo->isGame = true;
    gameInfo->isVictory = 0;
    gameInfo->lastFigurePos = 8;
    gameInfo->newFigurePos = 16;
    gameInfo->movesID = 0;
}

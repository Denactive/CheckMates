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

void Database::setAllMessagesFromQuery()
{
    QSqlQuery query = QSqlQuery(this->database());
    if (!query.exec("SELECT _id, text, chatID FROM Messages")) {
        qDebug() << query.lastError().databaseText();
        qDebug() << query.lastError().driverText();
    }

    while (query.next())
    {
        MsgInfo newMsgInfo;
        QString text = query.value(1).toString();
        int chatID = query.value(2).toInt();

        newMsgInfo.text = text;
        newMsgInfo.chatID = chatID;

        messagesInfo.push_back(newMsgInfo);
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
        Chat *newChat = new Chat();
        if (chatID == -1)
            if (!query.next()) break;
        qDebug() << "chatID" << chatID;
        while (chatID <= fillChatID) {
            chatID = query.value(2).toInt();
            QString text = query.value(1).toString();
            qDebug() << "add: " << text;

            bool fromWho = query.value(3).toBool();
            MyMessage msg(text, fromWho);
            newChat->addMessage(msg);

            qDebug() << "new chatID" << chatID;
            if (!query.next()) break;
        }
        fillChatID = chatID;
        chatsInfo.push_back(newChat);

        if (!query.isValid()) break;
    }

//    for (auto & value : chatsInfo) {
//       std::vector<MyMessage> msgs = value->getMessages();
//       for (auto & msg : msgs)
//           qDebug() << msg.getMessage();
//    }
}

#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include <QtSql/QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlRecord>
#include <QString>
#include <memory>
#include <vector>

#include "../include/community.h"

struct UserInfo {
    QString name;
    QString login;
    QString password;
    QString photoPath;
    int rating;
};

struct MsgInfo {
    QString text;
    int chatID;
};

struct GameInfo {
    bool currentPlayer; // true - me, false - opponent
    bool isCheck; // true - is shax
    bool isGame; // false - quit game
    int isVictory; // 0 - draw, 1 - me, 2 - opponent
    int lastFigurePos; // [0-63]
    int newFigurePos;
};

class IDatabase {
    virtual void setUserDataFromQuery() = 0;
    virtual std::vector<UserInfo> getUsersData() = 0;
    virtual void setAllMessagesFromQuery() = 0;
    virtual std::vector<MsgInfo> getAllMessages() = 0;

};

class Database : public QSqlDatabase,  public IDatabase
{
public:
    Database();
    void setUserDataFromQuery() override;
    std::vector<UserInfo> getUsersData() override { return usrInfo; }
//    void setChatDataFromQuery() override;
//    std::vector<Chat> getChatsData() override { return chatsInfo; }
    void setAllMessagesFromQuery() override;
    std::vector<MsgInfo> getAllMessages() override { return messagesInfo; }
    void fillChats();
    std::vector<Chat*> getChats() { return chatsInfo; }

private:
    std::vector<UserInfo> usrInfo;
    std::vector<MsgInfo> messagesInfo;
    std::vector<Chat*> chatsInfo;
};

struct Stats {
    int avgGameLen;
    int movesToWinQuantity;
    int staleMatePercentage;
    int gameLeavingPercentage;
    int giveUpsPercentage;
};

class IStatistics {
    virtual Stats * getStats(User * user) = 0;
    virtual int getAverageGameLen() = 0;
    virtual int getAverageMovesToWinQuantity()= 0;
    virtual int getStaleMatePercentage() = 0;
    virtual int getGameLeavingPercentage() = 0;
    virtual int giveUpsPercentage() = 0;
};


class Statistics : public IStatistics {
public:
    Stats * getStats(User * user) override { return nullptr; }
    int getAverageGameLen() override { return -1; }
    int getAverageMovesToWinQuantity() override { return -1; }
    int getStaleMatePercentage() override { return -1; }
    int getGameLeavingPercentage() override { return -1; }
    int giveUpsPercentage() override { return -1; }
};

#endif // DATABASE_H

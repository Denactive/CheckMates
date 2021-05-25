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
#define DEBUGDATA 0

typedef struct {
    QString name;
    QString login;
    QString password;
    QString photoPath;
    int rating;
} UserInfo;

typedef struct {
    QString text;
    int chatID;
} MsgInfo;

typedef struct {
    int move;
} MovesInfo;

typedef struct {
    int meId;
    int opponentId;
    bool currentPlayer; // true - me, false - opponent
    bool isCheck; // true - is shax
    bool isGame; // false - quit game
    int isVictory; // 0 - draw, 1 - me, 2 - opponent
    int lastFigurePos; // [0-63]
    int newFigurePos;
    int movesID; // доступные ходы
} GameInfo;

class IDatabase {
    virtual void setUserDataFromQuery() = 0;
    virtual std::vector<UserInfo> getUsersData() = 0;
};

class Database : public QSqlDatabase,  public IDatabase
{
public:
    Database();
    void setUserDataFromQuery() override;
    std::vector<UserInfo> getUsersData() override { return usrInfo; }
    void fillChats();
    std::vector<std::shared_ptr<Chat>> getChats() { return chatsInfo; }
    std::shared_ptr<User> findUser(int index);

    void setGameInfoFromQuery();
    std::shared_ptr<GameInfo> getGameInfo() { return gameInfo; }

private:
    std::vector<UserInfo> usrInfo;
    std::vector<std::shared_ptr<Chat>> chatsInfo;
    std::shared_ptr<GameInfo> gameInfo;
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

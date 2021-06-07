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

// after login
typedef struct {
    int id;
    QString name;
    QString login;
    QString password;
    // QString photoPath;
    QPixmap photo;
    int rating;
} UserInfo;

// after start game
typedef struct {
    QString gameToken;
    int uid;
    bool side; // true - white, false - black
    QString nameOpponent;
    int ratingOpponent;
    QPixmap avatarOpponent;
} StartGame;

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
    bool currentPlayer; // true - white, false - black
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
    void addUser(int id, QString name, QString login = "", QString password = "", QPixmap photo = QPixmap(), int rating = 0);
    void fillChats();
    std::vector<std::shared_ptr<Chat>> getChats() { return chatsInfo; }
    std::shared_ptr<User> findUser(int index);

    void setGameInfoFromQuery();
    std::shared_ptr<GameInfo> getGameInfo() { return gameInfo; }

    void setStartGameInfo(std::shared_ptr<QString> gameToken, int uid, std::shared_ptr<QString> nameOpponent, int ratingOpponent, std::shared_ptr<QPixmap>  avatarOpponent, bool side);
    std::shared_ptr<StartGame> getStartGameInfo() { return startGame; }

private:
    std::vector<UserInfo> usrInfo;
    std::vector<std::shared_ptr<Chat>> chatsInfo;
    std::shared_ptr<GameInfo> gameInfo;
    std::shared_ptr<StartGame> startGame;
};

#endif // DATABASE_H

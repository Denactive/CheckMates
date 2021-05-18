#ifndef SERVER_USER_H
#define SERVER_USER_H

#include <vector>

#include "community.h"
#include "ServerDB.h"

typedef struct {
    std::string ip;
    // sock
} Connection;

typedef enum {
    unqualified,
    begginer,
    fan,
    enjoyer,
    pro,
    grossmaster
} UserStatus;

typedef struct {
    double winrate;
    double rating_dynamics;
    double avg_game_len;
    double avg_moves_to_win;
    double stalemate_percentage;
    double game_leaving_percentage;
    double draw_percentage;
    double give_up_percentage;
} Stats;

typedef size_t uid;

typedef struct {
    uid id;
    int rating;
} UserInfo;

class IStats {
public:
    virtual Stats get_user_info(uid id, IDBServer& db) = 0;
    virtual Stats get_user_stats(uid id, IDBServer& db) = 0;
};

class StatsAgregator: IStats {
public:
    Stats get_user_info(uid id, IDBServer& db) override;
    Stats get_user_stats(uid id, IDBServer& db) override;
};


class IUser {
public:
    virtual UserInfo  get_info() = 0;
    virtual uid get_id() = 0;
    virtual std::string get_nickname() = 0;
    virtual int get_rating() = 0;
    virtual void set_rating(int) = 0;
    virtual Stats get_full_stats(IDBServer&) = 0;
    virtual ICommunity* create_community() = 0;
    virtual IChat* create_chat(std::set<uid> members) = 0;
};

class User: public IUser {
public:
    explicit User(Connection& connection, uid id, std::string nickname, std::vector<IChat*> chat_list, UserStatus status);
    // TODO: remove test c-tor
    explicit User(Connection& connection = *(new Connection));
    ~User() {};

    UserInfo get_info() override;
    uid get_id() override { return id_; }
    std::string get_nickname() override { return nickname_; }
    int get_rating() override { return rating_; }
    Stats get_full_stats(IDBServer& db) override;

    void set_rating(int new_rating) override { rating_ = new_rating; }

    ICommunity* create_community() override;
    IChat* create_chat(std::set<uid> members) override;

private:
    Connection& connection_;
    uid id_;
    StatsAgregator stats_getter_;
    std::string nickname_;
    int rating_;
    std::vector<IChat*> chat_list_;
    UserStatus status_;
};

class IAuthorizer {
public:
    virtual IUser* authorize(Connection& con, IDBServer& db) = 0;
    virtual IUser* registrate(Connection& con, IDBServer& db) = 0;
};

class Authorizer: IAuthorizer {
public:
    IUser* authorize(Connection& con, IDBServer& db) override;
    IUser* registrate(Connection& con, IDBServer& db) override;
};

#endif //SERVER_USER_H


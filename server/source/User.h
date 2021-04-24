#ifndef SERVER_USER_H
#define SERVER_USER_H

#include "GameSession.h"
#include "net.h"
#include "community.h"
#include "matcher.h"

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
    virtual Stats get_user_info(uid id) = 0;
    virtual Stats get_user_stats(uid id) = 0;
};

class StatsAgregator: IStats {
public:
    Stats get_user_info(uid id) override;
    Stats get_user_stats(uid id) override;
};


class IUser {
public:
    virtual UserInfo  get_info() = 0;
    virtual uid get_id() = 0;
    virtual std::string get_nickname() = 0;
    virtual int get_rating() = 0;
    virtual void set_rating(int) = 0;
    virtual void enter_mq(IMatcherQueue&) = 0;
    virtual void leave_mq(IMatcherQueue&) = 0;
    virtual Stats get_full_stats() = 0;
    virtual ICommunity& create_community() = 0;
    virtual IChat& create_chat(std::set<uid> members) = 0;
};

class User: public IUser {
public:
    User(Connection& connection, uid id, std::string nickname, std::vector<IChat*> chat_list, UserStatus status):
        connection_(connection), id_(id), nickname_(nickname), chat_list_(chat_list), status_(status) {
        // todo: сходить в базу, взять userinfo | сохранить конекшн
    }
    UserInfo get_info() override;
    uid get_id() override { return id_; }
    std::string get_nickname() override { return nickname_; }
    int get_rating() override { return rating_; }
    void set_rating(int new_raiting) override { rating_ = new_raiting; }
    // TODO: разобраться с этим. Перенести в net ?
    void enter_mq(IMatcherQueue& mq) override { mq.push_user(this); }
    void leave_mq(IMatcherQueue& mq) override { mq.pop_user(this); }
    Stats get_full_stats() override;

    ICommunity& create_community() override;
    IChat& create_chat(std::set<uid> members) override;

protected:
    Connection& connection_;
    uid id_;
    StatsAgregator stats_getter_;
    std::string nickname_;
    int rating_;
    std::vector<IChat*> chat_list_;
    UserStatus status_;
};


class IAuthorizer {
    virtual IUser& authorize(Connection& con) = 0;
    virtual IUser& registrate(Connection& con) = 0;
};

class Authorizer: IAuthorizer {
    IUser& authorize(Connection& con) override;
    IUser& registrate(Connection& con) override;
};

#endif //SERVER_USER_H

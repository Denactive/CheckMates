//
// Created by denactive on 15.04.2021.
//

#ifndef CHECKMATES_USER_H
#define CHECKMATES_USER_H

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

class IStats {
public:
    virtual Stats get_user_info(size_t uid) = 0;
    virtual Stats get_user_stats(size_t uid) = 0;
};

class IUser {
public:
    virtual std::string get_info() = 0;
    virtual size_t get_id() = 0;
    virtual std::string get_nickname() = 0;
    virtual int get_raiting() = 0;
    virtual void set_raiting(int new_raiting) = 0;
    virtual void enter_mq(IMatcherQueue&) = 0;
    virtual void leave_mq(IMatcherQueue&) = 0;
    virtual Stats get_full_stats() = 0;
    virtual ICommunity& create_community() = 0;
    virtual IChat& create_chat() = 0;
};

class User: IUser {
public:
    User(Connection& connection, size_t id, std::string nickname, std::vector<IChat*> chat_list, UserStatus status):
        connection_(connection), id_(id), nickname_(nickname), chat_list_(chat_list), status_(status) {

    }
    std::string get_info() override;
    size_t get_id() override { return id_; }
    std::string get_nickname() override { return nickname_; }
    int get_raiting() override { return raiting_; }
    void set_raiting(int new_raiting) override { raiting_ = new_raiting; }
    //void enter_mq(IMatcherQueue) override;
    //void leave_mq(IMatcherQueue) override;
    Stats get_full_stats() override;

protected:
    Connection& connection_;
    size_t id_;
    std::string nickname_;
    int raiting_;
    std::vector<IChat*> chat_list_;
    UserStatus status_;
};

class StatsAgregator: IStats {
public:
    Stats get_user_info(size_t uid) override;
    Stats get_user_stats(size_t uid) override;
};

class IAuthorizer {
    virtual IUser& authorize(Connection& con) = 0;
    virtual IUser& registrate(Connection& con) = 0;
};

class Authorizer: IAuthorizer {
    IUser& authorize(Connection& con) override;
    IUser& registrate(Connection& con) override;
};

#endif //CHECKMATES_USER_H

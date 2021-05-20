#ifndef SERVER_USER_H
#define SERVER_USER_H

#include <vector>
#include <functional>
#include <memory>
#define TEST_USER 1

class WebSocketSession;
class Session;

#include "community.h"
#include "ServerDB.h"


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
    std::string nickname;
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
    virtual void set_user_data(uid, std::string, int) = 0;
    virtual Stats get_full_stats(IDBServer&) = 0;
    virtual ICommunity* create_community() = 0;
    virtual IChat* create_chat(std::set<uid> members) = 0;
    virtual void set_http_session(std::shared_ptr<Session>& s) = 0;
};

class User: public IUser {
public:
    time_t token = 0;
    //std::function< void(http::message<false, http::string_body, http::fields>) > confirm_game_start_;

    User()
    //   : confirm_game_start_(send)
    {
        if (TEST_USER) {
            id_ = 1;
            rating_ = 15;
            nickname_ = "Sveta";
        }
    }

    ~User() {};

    UserInfo get_info() override;
    uid get_id() override { return id_; }
    std::string get_nickname() override { return nickname_; }
    int get_rating() override { return rating_; }
    Stats get_full_stats(IDBServer& db) override;
    bool is_http_session_valid() { return http_session != nullptr;  }

    // test
    void set_user_data(uid id, std::string nickame, int new_rating) override { rating_ = new_rating; id_ = id; nickname_ = nickame; }
    void set_rating(int new_rating) override { rating_ = new_rating; }
    void set_http_session(std::shared_ptr<Session>& s) override { http_session = s; }
   

    ICommunity* create_community() override;
    IChat* create_chat(std::set<uid> members) override;

private:

    std::shared_ptr<WebSocketSession> session_ = nullptr;
    uid id_;
    StatsAgregator stats_getter_;
    std::string nickname_;
    int rating_;
    std::vector<IChat*> chat_list_;
    UserStatus status_;
    std::shared_ptr<Session> http_session = nullptr;
};

struct UserComparator {
    bool operator()(const std::shared_ptr<User>& lhs, const std::shared_ptr<User>& rhs) const {
        return lhs->token < rhs->token;
    }
};

typedef std::set<std::shared_ptr<User>, UserComparator> UserSet;

class IAuthorizer {
public:
    virtual IUser* authorize(WebSocketSession& con, IDBServer& db) = 0;
    virtual IUser* registrate(WebSocketSession& con, IDBServer& db) = 0;
};

class Authorizer: public IAuthorizer {
public:
    IUser* authorize(WebSocketSession& con, IDBServer& db) override;
    IUser* registrate(WebSocketSession& con, IDBServer& db) override;
};

#endif //SERVER_USER_H


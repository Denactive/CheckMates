#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#ifndef SERVER_USER_H
#define SERVER_USER_H
#define BOOST_DATE_TIME_NO_LIB

//#include<boost/asio/steady_timer.hpp>
//#include <boost/asio/dispatch.hpp>
//#include <boost/asio/strand.hpp>

#include <chrono>
#include <ctime>
#include <memory>
#include <sstream>
#include <vector>
#include <map>

#include <functional>

#define TEST_USER 1

class WebSocketSession;
class Session;

#include "community.h"
#include "ServerDB.h"

typedef size_t uid;
typedef std::chrono::system_clock::time_point timepoint;
typedef std::chrono::system_clock::time_point Cookie;
typedef std::chrono::system_clock::time_point GameToken;

std::string static serializeTimePoint(const timepoint& time, const std::string& format = "%y-%m-%d-%H_%M_%S")
{
    std::time_t tt = std::chrono::system_clock::to_time_t(time);
    std::tm tm;
#ifdef _WIN32
    if (localtime_s(&tm, &tt)) //Locale time-zone, usually UTC by default.
        return "undefined_time";
#else
    localtime_r(&tt, &tm);
#endif
    char mbstr[64];
    std::stringstream ss;

    if (std::strftime(mbstr, 64, format.c_str(), &tm))
        ss << mbstr;
    else
        ss << "undefined_time";

    return ss.str();
}

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
    virtual Cookie get_token() = 0;
    virtual std::string get_token_string() = 0;
    virtual std::string get_avatar() = 0;
};

class User: public IUser {
public:
    User()
        : token_(std::chrono::system_clock::now())
    {
        if (TEST_USER) {
            id_ = 1;
            rating_ = 15;
            nickname_ = "Sveta";
            avatar_ = "/users/avatars/sveta.png";
        }
    }

    ~User() {};

    UserInfo get_info() override;
    uid get_id() override { return id_; }
    std::string get_nickname() override { return nickname_; }
    std::string get_avatar() override { return avatar_; }
    int get_rating() override { return rating_; }
    Stats get_full_stats(IDBServer& db) override;
    Cookie get_token() override { return token_; };
    std::string get_token_string() override { return serializeTimePoint(token_); }

    // test
    void set_user_data(uid id, std::string nickame, int new_rating) override { rating_ = new_rating; id_ = id; nickname_ = nickame; }
    void set_rating(int new_rating) override { rating_ = new_rating; }
   

    ICommunity* create_community() override;
    IChat* create_chat(std::set<uid> members) override;

private:

    StatsAgregator stats_getter_;
    
    uid id_;
    std::string nickname_;
    int rating_;
    std::string avatar_;
    std::vector<IChat*> chat_list_;
    UserStatus status_;
    const Cookie token_;
};

// Unrequired
struct UserComparator {
    bool operator()(const std::shared_ptr<User>& lhs, const std::shared_ptr<User>& rhs) const {
        return lhs->get_token() < rhs->get_token();
    }
};

struct StringTokenComparator {
    bool operator () (const std::string& a, const std::string& b) const {
        return a > b;
    }
    static std::string max_value() {
        return "";
    }
};

typedef std::map< std::string, std::shared_ptr<IUser>, StringTokenComparator > UserMap;

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


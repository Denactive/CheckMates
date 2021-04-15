//
// Created by yura11011 on 15.04.2021.
//

#ifndef CHECKMATES_USER_H
#define CHECKMATES_USER_H
#include "GameSession.h"
#include "Stub.h"

class iUser{
public:
    virtual std::string get_info() = 0;
    virtual size_t get_id() = 0;
    virtual std::string get_nickname() = 0;
    virtual int get_rating() = 0;
    virtual void set_rating(int rating) = 0;
    virtual void enter_mq(MatcherQueue) = 0;
    virtual void leave_mq(MatcherQueue) = 0;
    virtual Stats get_full_stats() = 0;
    virtual Community create_community() = 0;
    virtual Chat create_chat() = 0;

};

class User : public iUser {
public:
    User();
    Connection& connection;
    size_t id;
    std::string nickname;
    int rating;
    std::vector <Chat> list_chats;
    std::string get_info();
    size_t get_id();
    std::string get_nickname();
    int get_rating();
    void set_rating(int rating);
    void enter_mq(MatcherQueue);
    void leave_mq(MatcherQueue);
    Stats get_full_stats();
    Community create_community();
    Chat create_chat();
    Chat create_chat(const User&);
};


#endif //CHECKMATES_USER_H

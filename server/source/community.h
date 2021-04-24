//
// Created by denactive on 15.04.2021.
//
#ifndef CHECKMATES_COMMUNITY_H
#define CHECKMATES_COMMUNITY_H

#include <set>
#include <string>

typedef enum {
    get_10_participants,
    get_100_participants,
    get_1000_participants,
} Rewards;

class IChat {
public:
    virtual std::string get_history() = 0;
    virtual void add_message(size_t uid, std::string msg) = 0;
    virtual void modify_history(std::string s) = 0;
    virtual std::set<size_t> get_user_list() = 0;
};

class Chat: public IChat {
public:
    Chat(std::set<size_t> users):
            list_members_(users) {
    }
    Chat() {};
    std::string get_history() override { return history_; }
    std::set<size_t> get_user_list() override { return list_members_; }
    void modify_history(std::string s) override {};
    void add_message(size_t uid, std::string msg) override {};

private:
    std::set<size_t> list_members_;
    std::string history_;
};

class ICommunity {
public:
    virtual void modify() = 0;
    virtual void accept_user(size_t u) = 0;
    virtual std::set<size_t> get_user_list() = 0;
    virtual std::set<size_t> get_moderators_list() = 0;
    virtual size_t get_admin() = 0;
    virtual std::set<Rewards> get_rewards() = 0;
    virtual IChat& get_group_chat() = 0;

    virtual void set_admin(size_t) = 0;
    virtual void add_reward(Rewards r) = 0;
    virtual void add_moderator(size_t) = 0;
};

class Community: public ICommunity {
public:
    Community(Chat& group_chat = *(new Chat)): group_chat_(group_chat){};
    void modify() override {};
    void accept_user(size_t uid) override {};
    std::set<size_t> get_user_list() override{
        std::set<size_t> set;
        return set;
    };
    std::set<size_t> get_moderators_list() override{
        std::set<size_t> set;
        return set;
    };
    size_t get_admin() override{
        return 0;
    };
    std::set<Rewards> get_rewards() override{
        std::set<Rewards> set;
        return set;
    };
    IChat& get_group_chat() override{
        Chat& chat = *(new Chat);
        return chat;
    };

    void set_admin(size_t) override{};
    void add_reward(Rewards r) override{};
    void add_moderator(size_t) override{};

private:
    std::set<size_t> list_members_;
    std::set<size_t> list_moderators_;
    size_t admin_;
    std::set<Rewards> rewards_;
    IChat& group_chat_;
};

#endif //CHECKMATES_COMMUNITY_H

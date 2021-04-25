//
// Created by denactive on 15.04.2021.
//
#ifndef CHECKMATES_COMMUNITY_H
#define CHECKMATES_COMMUNITY_H

#include <iostream>
#include <set>
#include <string>

typedef size_t uid;

typedef enum {
    get_10_participants,
    get_100_participants,
    get_1000_participants,
} Rewards;

class IChat {
public:
    virtual std::string get_history() = 0;
    virtual std::set<uid> get_user_list() = 0;
    virtual void modify_history(std::string s) = 0;
    virtual void add_message(uid id, std::string msg) = 0;
};

class Chat: public IChat {
public:
    Chat(std::set<uid> users): list_members_(users) {
            std::cout << "Chat user list c-tor\n";
            history_ = "hist";
    }
    Chat() { std::cout << "Chat default c-tor\n"; }
    ~Chat() { std::cout << "Chat default des-tor\n"; }

    std::string get_history() override { return history_; }
    std::set<uid> get_user_list() override { return list_members_; }
    void modify_history(std::string s) override;
    void add_message(uid id, std::string msg) override;

private:
    std::set<uid> list_members_;
    std::string history_;
};

class ICommunity {
public:
    virtual void modify() = 0;
    virtual void accept_user(uid u) = 0;
    virtual std::set<uid> get_user_list() = 0;
    virtual std::set<uid> get_moderators_list() = 0;
    virtual uid get_admin() = 0;
    virtual std::set<Rewards> get_rewards() = 0;
    virtual Chat* get_group_chat() = 0;

    virtual void set_admin(uid) = 0;
    virtual void add_reward(Rewards r) = 0;
    virtual void add_moderator(uid) = 0;
};

class Community: public ICommunity {
public:
    Community(std::set<uid> list_members): group_chat_(Chat(list_members)) {
        std::cout << "Community list_members c-tor\n";
    };

    void modify() override {};
    void accept_user(size_t uid) override {};

    std::set<size_t> get_user_list() override{
        std::set<size_t> set;
        return set;
    }

    std::set<size_t> get_moderators_list() override{
        std::set<size_t> set;
        return set;
    }

    size_t get_admin() override{
        return 0;
    }

    std::set<Rewards> get_rewards() override{
        std::set<Rewards> set;
        return set;
    }

    Chat* get_group_chat() override{
        Chat* chat = nullptr;
        return chat;
    }

    // TODO: check user for rights to be admin / moderator/ to be in the Community
    void set_admin(uid id) override { admin_ = id; };
    void add_reward(Rewards r) override { rewards_.insert(r); };
    void add_moderator(uid id) override { list_moderators_.insert(id); };

private:
    std::set<uid> list_members_;
    std::set<uid> list_moderators_;
    uid admin_;
    std::set<Rewards> rewards_;
    Chat group_chat_;
};

#endif //CHECKMATES_COMMUNITY_H

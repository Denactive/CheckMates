//
// Created by denactive on 15.04.2021.
//
#ifndef CHECKMATES_COMMUNITY_H
#define CHECKMATES_COMMUNITY_H

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
    virtual void add_message(uid id, std::string msg) = 0;
    virtual void modify_history(std::string s) = 0;
    virtual std::set<uid> get_user_list() = 0;
};

class Chat: IChat {
public:
    Chat(std::set<uid> users):
            list_members_(users) {
    }
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
    virtual IChat& get_group_chat() = 0;

    virtual void set_admin(uid) = 0;
    virtual void add_reward(Rewards r) = 0;
    virtual void add_moderator(uid) = 0;
};

class Community: ICommunity {
public:
    Community();
    void modify() override;
    void accept_user(uid uid) override;
    std::set<uid> get_user_list() override;
    std::set<uid> get_moderators_list() override;
    uid get_admin() override;
    std::set<Rewards> get_rewards() override;
    IChat& get_group_chat() override;

    void set_admin(uid) override;
    void add_reward(Rewards r) override;
    void add_moderator(uid) override;

private:
    std::set<uid> list_members_;
    std::set<uid> list_moderators_;
    uid admin_;
    std::set<Rewards> rewards_;
    IChat& group_chat_;
};

#endif //CHECKMATES_COMMUNITY_H

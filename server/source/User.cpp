//
// Created by denactive on 24.04.2021.
//
#include "User.h"

UserInfo User::get_info() {
    UserInfo res;
    res.id = this->id_;
    res.rating = this->rating_;
    return res;
}

Stats User::get_full_stats() {
    return stats_getter_.get_user_info(this->id_);
}
//TODO: fix that
//ICommunity& User::create_community() override {
//    Community* c = new Community();
//    return *c;
//}
//
//IChat& User::create_chat(std::set<size_t> members) override {
//    Chat* c = new Chat(members);
//    return *c;
//}
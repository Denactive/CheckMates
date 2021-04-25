//
// Created by denactive on 24.04.2021.
//
#include "User.h"

//TODO: fix that
//ICommunity& User::create_community() override {
//    Community* c = new Community();
//    return *c;
//}
//
//IChat& User::create_chat(std::set<uid> members) override {
//    Chat* c = new Chat(members);
//    return *c;
//}

User::User(Connection &connection, uid id, std::string nickname, std::vector<IChat *> chat_list, UserStatus status) :
        connection_(connection), id_(id), nickname_(nickname), chat_list_(chat_list), status_(status) {

}

User::User(Connection &connection) : connection_(connection) {

};

UserInfo User::get_info() {
    UserInfo res;
    res.id = this->id_;
    res.rating = this->rating_;
    return res;
}

Stats User::get_full_stats(IDBServer& db) {
    return stats_getter_.get_user_stats(this->id_, db);
}

// this function allocates memory!
ICommunity* User::create_community() {
    std::set<uid> member_list;
    // add somebody
    Community* community = new Community(member_list);
    return community;
};

// this function allocates memory!
IChat* User::create_chat(std::set<uid> members) {
    Chat* chat = new Chat;
    return chat;
};

//
//  Authorizer
//


// this function allocates memory!
IUser* Authorizer::authorize(Connection& con, IDBServer& db) {
    // TODO: tuples
    std::string user_data = db.query("SELECT username... FROM db.users");
    User* res = nullptr; //new User();;
    return res;
}

// this function allocates memory!
IUser* Authorizer::registrate(Connection& con, IDBServer& db) {
    std::string user_data = db.query("SELECT username... FROM db.users");
    User* res = nullptr; //new User();;
    return res;
}


//
// stats agregator
//

Stats StatsAgregator::get_user_info(uid id, IDBServer& db) {
    return {0};
}

Stats StatsAgregator::get_user_stats(uid id, IDBServer& db) {
    return {0};
}

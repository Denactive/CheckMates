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
IUser* Authorizer::authorize(Session& con, IDBServer& db) {
    // TODO: tuples
    std::string user_data = db.query("SELECT username... FROM db.users");
    User* res = nullptr; //new User();;
    return res;
}

// this function allocates memory!
IUser* Authorizer::registrate(Session& con, IDBServer& db) {
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

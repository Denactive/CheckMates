//
// Created by denactive on 24.04.2021.
//

#include "User.h"

Stats User::get_full_stats(IDBServer& db) {
    return stats_getter_.get_user_stats(this->id_, db);
}

// this function allocates memory!
std::shared_ptr<ICommunity> User::create_community() {
    return nullptr;
};

// this function allocates memory!
std::shared_ptr<IChat> User::create_chat(std::set<uid> members) {
    return nullptr;
};

//
//  Authorizer
//


IUser* Authorizer::authorize(WebSocketSession& con, IDBServer& db) {
    db_error ec;
    std::string user_data = db.query("SELECT name FROM users WHERE name=Sveta", ec);
    User* res = nullptr;
    return res;
}

// this function allocates memory!
IUser* Authorizer::registrate(WebSocketSession& con, IDBServer& db) {
    db_error ec;
    std::string user_data = db.query("SELECT name FROM users WHERE name=Sveta", ec);
    User* res = nullptr;
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

//
// Created by denactive on 23.04.2021.
//

#ifndef SERVER_RESTATS_H
#define SERVER_RESTATS_H

class reStats: public IStats {
public:
    MOCK_METHOD(Stats, get_user_info, (size_t user_id, IDBServer&), (override));
    MOCK_METHOD(Stats, get_user_stats, (size_t user_id, IDBServer&), (override));
};

#endif //SERVER_RESTATS_H

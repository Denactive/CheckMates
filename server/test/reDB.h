//
// Created by denactive on 25.04.2021.
//

#ifndef SERVER_REDB_H
#define SERVER_REDB_H

class reDB: public IDBServer {
public:
    MOCK_METHOD(std::string, query, (std::string, db_error&), (override));
    MOCK_METHOD0(Die, void());
    virtual ~reDB() { Die(); }
};
#endif //SERVER_REDB_H

//
// Created by denactive on 25.04.2021.
//

#ifndef SERVER_REDB_H
#define SERVER_REDB_H

class reDB: public IDBServer {
public:
    MOCK_METHOD(std::string, query, (std::string), (override));
    MOCK_METHOD(std::string, read, (), (override));
    MOCK_METHOD(void, write, (std::string), (override));
};

class fakeDB: public IDBServer {
public:
    std::string query(std::string q) { return "test_query"; }
    std::string read() { return "test_read"; }
    void write(std::string q) {}
};

#endif //SERVER_REDB_H

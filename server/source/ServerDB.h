#ifndef CHECKMATES_SERVERDB_H
#define CHECKMATES_SERVERDB_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <memory>

typedef enum {
    OK,
    invalid_command,
    invalid_record,
    no_table,
    unsupported,
    not_found
} db_error;

class IDBServer {
public:
    virtual std::string query(std::string, db_error&) = 0;
};

class DBServer: public IDBServer {
public:
    DBServer(const std::string filepath): doc_root_(filepath)
    {
        tables_.push_back("users");
    }
    DBServer() = default;
    std::string query(std::string, db_error&) override;

private:
    const std::string doc_root_;
    std::vector<std::string> tables_;

    std::string parse_error(const db_error&);
};

#endif //CHECKMATES_SERVERDB_H

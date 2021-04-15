//
// Created by denactive on 15.04.2021.
//

#ifndef CHECKMATES_SERVERDB_H
#define CHECKMATES_SERVERDB_H

#include <string>


class IDB_server {
public:
    virtual std::string query(std::string q) = 0;
};

class DB_server: IDB_server {
public:
    std::string query(std::string q) override;

private:
    std::string filepath_;
};


#endif //CHECKMATES_SERVERDB_H

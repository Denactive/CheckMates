#ifndef CHECKMATES_SERVERDB_H
#define CHECKMATES_SERVERDB_H

#include <string>

class IDBServer {
public:
    virtual std::string query(std::string q) = 0;
    virtual std::string read() = 0;
    virtual void write(std::string q) = 0;
};

class DBServer: public IDBServer {
public:
    DBServer(std::string filepath): filepath_(filepath) {

    }
    DBServer() = default;

    std::string query(std::string q) {return q;};
    std::string read() {return filepath_;};
    void write(std::string q) {filepath_ = q;};
private :
    std::string filepath_;
    std::string fileDB() { return ""; }
};

#endif //CHECKMATES_SERVERDB_H

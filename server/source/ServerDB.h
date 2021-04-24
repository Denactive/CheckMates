#ifndef CHECKMATES_SERVERDB_H
#define CHECKMATES_SERVERDB_H

#include <string>


class iBDServer {
public:
    virtual std::string query(std::string q) = 0;
    virtual std::string read() = 0;
    virtual void write(std::string q) = 0;
};

class BDServer: public iBDServer {
public:
    std::string query(std::string q) {return q;};
    std::string read() {return filepath_;};
    void write(std::string q) {filepath_ = q;};
private :
    std::string filepath_;
    std::string fileDB() {return 0;};
};



#endif //CHECKMATES_SERVERDB_H

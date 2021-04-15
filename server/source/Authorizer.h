

#ifndef CHECKMATES_AUTHORIZER_H
#define CHECKMATES_AUTHORIZER_H

class iBDServer {
public:
    virtual std::string query(std::string q) = 0;
};

class BDServer: public iBDServer {
public:
    std::string query(std::string q);
private :
    std::string fileDB();
};

#endif //CHECKMATES_AUTHORIZER_H

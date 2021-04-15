#ifndef CHECKMATES_AUTHORIZER_H
#define CHECKMATES_AUTHORIZER_H
#include "GameSession.h"

class iAuthorizer {
public:
    virtual User authorize(Connection& connection) = 0;
    virtual User register(Connection& connection) = 0;
};

class Authorizer: public iAuthorizer {
public:
    User authorize(Connection& connection);
    User register(Connection& connection);
private :
};

#endif //CHECKMATES_AUTHORIZER_H

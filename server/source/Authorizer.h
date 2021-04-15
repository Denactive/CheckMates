#ifndef CHECKMATES_AUTHORIZER_H
#define CHECKMATES_AUTHORIZER_H
#include "GameSession.h"
#include "Stub.h"

class iAuthorizer {
public:
    virtual User authorize() = 0;
    virtual User registration() = 0;
};

class Authorizer: public iAuthorizer {
public:
    User authorize();
    User registration();
private :
};

#endif //CHECKMATES_AUTHORIZER_H

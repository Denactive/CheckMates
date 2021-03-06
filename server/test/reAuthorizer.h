//
// Created by denactive on 23.04.2021.
//

#ifndef SERVER_REAUTHORIZER_H
#define SERVER_REAUTHORIZER_H

class reAuthorizer: public IAuthorizer {
public:
    MOCK_METHOD(User*, authorize, (Connection&, IDBServer&), (override));
    MOCK_METHOD(User*, registrate, (Connection&, IDBServer&), (override));
};

#endif //SERVER_REAUTHORIZER_H

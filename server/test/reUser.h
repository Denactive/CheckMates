//
// Created by denactive on 23.04.2021.
//

#ifndef SERVER_REUSER_H
#define SERVER_REUSER_H

class reUser: IUser {
public:
//    MOCK_METHOD(std::string, get_info, (), (override));
    MOCK_METHOD(size_t, get_id, (), (override));
    MOCK_METHOD(std::string, get_nickname, (), (override));
    MOCK_METHOD(int, get_rating, (), (override));
    MOCK_METHOD(void, set_rating, (int), (override));
//    MOCK_METHOD(void, enter_mq, (IMatcherQueue&), (override));
//    MOCK_METHOD(void, leave_mq, (IMatcherQueue&), (override));
//    MOCK_METHOD(Stats, get_full_stats, (IDBServer&), (override));
//    MOCK_METHOD(ICommunity*, create_community ,(), (override));
//    MOCK_METHOD(IChat*, create_chat, (), (override));
};

#endif //SERVER_REUSER_H

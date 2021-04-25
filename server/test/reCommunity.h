//
// Created by svetlana on 25.04.2021.
//

#ifndef CHECKMATES_RECOMMUNITY_H
#define CHECKMATES_RECOMMUNITY_H

class MockChat: public Chat  {
public:
    MOCK_METHOD(std::string, get_history, ());
    MOCK_METHOD(std::set<uid>, get_user_list, ());
    MOCK_METHOD(void, modify_history, (std::string));
    MOCK_METHOD(void, add_message, (uid, std::string));
};

class MockCommunity: public Chat  {
public:
    MOCK_METHOD(void, modify, ());
    MOCK_METHOD(void, accept_user, (uid));
    MOCK_METHOD(std::set<uid>, get_user_list, ());
    MOCK_METHOD(std::set<uid>, get_moderators_list, ());
    MOCK_METHOD(uid, get_admin, ());
    MOCK_METHOD(std::set<Rewards>, get_rewards, ());
    MOCK_METHOD(Chat*, get_group_chat, ());
    MOCK_METHOD(void, set_admin, (uid));
    MOCK_METHOD(void, add_reward, (Rewards));
    MOCK_METHOD(void, add_moderator, (uid));
};

#endif //CHECKMATES_RECOMMUNITY_H

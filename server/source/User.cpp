#include "User.h"
User::User(Connection& connection, size_t id, std::string nickname, std::vector<IChat*> chat_list, UserStatus status):
connection_(connection), id_(id), nickname_(nickname), chat_list_(chat_list), status_(status) {

}
User::User(Connection& connection): connection_(connection) {};
std::string User::get_info()  {return "new";};
size_t User::get_id()  { return id_; }
std::string User::get_nickname()  { return nickname_; }
int User::get_raiting()  { return raiting_; }
void User::set_raiting(int new_raiting)  { raiting_ = new_raiting; }
//void enter_mq(IMatcherQueue) override;
//void leave_mq(IMatcherQueue) override;
Stats User::get_full_stats()  {
Stats stats;
return stats;
};

//virtual void enter_mq(IMatcherQueue&) = 0;
//virtual void leave_mq(IMatcherQueue&) = 0;
ICommunity& User::create_community()  {
Community& community = *(new Community);
return community;
};
IChat& User::create_chat()  {
Chat& chat = *(new Chat);
return chat;
};
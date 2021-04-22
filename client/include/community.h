#ifndef COMMUNITY_H
#define COMMUNITY_H
//#include "../graphics.h"
#include <string>
#include <vector>

class User;
class Message;
class Chat;

class IUser {
public:
    virtual ~IUser() = default;
    virtual int getUserRating() const = 0;
    virtual std::string getUserPassword() const = 0;
    virtual std::string getLogin() const = 0;
    virtual int gameTime() const = 0;
    virtual std::pair<int, int> getUserStep() const = 0;
    virtual int changeRating(int newRating) const = 0;
    virtual void setPassword(std::string password) = 0;
    virtual void setLogin(std::string login) = 0;
};

class User : public IUser {
public:
    User(int nrating = 0, std::string npassword = "", std::string nlogin = "", int ntime = 0) 
    	:rating(nrating), password(npassword), login(nlogin), time(ntime) {};
    int getUserRating() const override { return -1; }
    std::string getUserPassword() const override { return ""; };
    std::string getLogin() const override { return ""; };
    int gameTime() const override { return -1; }
    std::pair<int, int> getUserStep() const override { return std::pair<int, int>(1, 1); }
    int changeRating(int newRating) const override { return newRating; }
    void setPassword(std::string password) override { this->password = password; }
    void setLogin(std::string login) override { this->login = login; };
private:
    int rating;
    std::string password;
    std::string login;
    int time;
    std::pair<int, int> step;
};


class MyMessage {
public:
    bool changeMessage(std::string new_message) { return false; }
    std::string getMessage() const { return ""; };
private:
    std::string message;
};


class Chat {
public:
    bool addMessage() { return false; };
    bool deleteMessage(int index) { return false; }
    bool cleanAllMessages() { return false; }
private:
    std::vector<MyMessage*> messages;
    User * user;
};

#endif // COMMUNITY_H

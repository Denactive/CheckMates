#ifndef COMMUNITY_H
#define COMMUNITY_H
#include "../include/graphics.h"

class User;
class Message;
class Chat;

class IUser {
public:
    virtual int getUserRating() const = 0;
    virtual std::string getUserPassword() const = 0;
    virtual std::string getLogin() const = 0;
    virtual std::string gameTime() const = 0;
    virtual std::pair<int, int> getUserStep() const = 0;
    virtual int changeRating() const = 0;
    virtual void setPassowrd(std::string password) = 0;
    virtual void setLogin(std::string login) = 0;
};

class User : public IUser {
public:
    User(int nrating = 0, std::string npassword = "", std::string nlogin = "", int ntime = 0) 
    	:rating(nrating), password(npassword), login(nlogin), time(ntime) {};
    int getUserRating() const override;
    std::string getUserPassword() const override;// { return password; };
    std::string getLogin() const override;// { return login; };
    std::string gameTime() const override;
    std::pair<int, int> getUserStep() const override;
    int changeRating() const override;
    void setPassowrd(std::string password) override; //{};
    void setLogin(std::string login) override; // {};
private:
    int rating;
    std::string password;
    std::string login;
    int time;
    std::pair<int, int> step;
};


class Message {
public:
    bool changeMessage(std::string new_message);
    std::string getMessage() const;
private:
    std::string message;
};


class Chat {
public:
    bool addMessage();
    bool deleteMessage(int index);
    bool cleanAllMessages();
private:
    Message * messages;
    User * user;
};

#endif // COMMUNITY_H

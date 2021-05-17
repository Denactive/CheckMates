#ifndef COMMUNITY_H
#define COMMUNITY_H

#include <string>
#include <vector>
#include <QPixmap>
#include <QString>
#include <QDebug>

class IUser {
public:
    virtual ~IUser() = default;
    virtual int getUserRating() const = 0;
    virtual QString getUserPassword() const = 0;
    virtual QString getLogin() const = 0;
    virtual int gameTime() const = 0;
    virtual std::pair<int, int> getUserStep() const = 0;
    virtual int changeRating(int newRating) const = 0;
    virtual void setPassword(QString password) = 0;
    virtual void setLogin(QString login) = 0;
};

class User : public IUser {
public:
    User(QString name = "", int nrating = 0, QString npassword = "", QString nlogin = "",
         QString photopath = "../img/userPhoto.png", int ntime = 100);
    void setUserPhoto(QPixmap photo) { this->photo = photo; };
    QPixmap getUserPhoto() { return photo; }
    void setName(QString name) { this->name = name; };
    QString getName() { return name; }

    int getUserRating() const override { return -1; }
    QString getUserPassword() const override { return ""; };
    QString getLogin() const override { return ""; };
    int gameTime() const override { return time; }
    std::pair<int, int> getUserStep() const override { return std::pair<int, int>(1, 1); }
    int changeRating(int newRating) const override { return newRating; }
    void setPassword(QString password) override { this->password = password; }
    void setLogin(QString login) override { this->login = login; };
private:
    QPixmap photo;
    QString name;
    int rating;
    QString password;
    QString login;
    int time;
    std::pair<int, int> step;
};


class MyMessage {
public:
    MyMessage(QString nmessage = "", bool fromWho = true): message(nmessage), fromWho(fromWho) {}
    void changeMessage(QString newMessage) { message = newMessage; }
    QString getMessage() const { return message; };
    bool getFromWho() { return fromWho; }
private:
    QString message;
    bool fromWho; // true = from me, false - from friend
};


class Chat {
public:
    Chat(User * nuser = nullptr) :user(nuser) {}
    void addMessage(MyMessage newMessage) { messages.push_back(newMessage); };
    void deleteMessage(int index) { messages.erase(messages.begin() + index); }
    void cleanAllMessages() { messages.clear(); }
    std::vector<MyMessage> getMessages() { return messages; };
    User * getUser() { return user; }
    MyMessage getLastMessage() { return messages[messages.size() - 1]; }
private:
    std::vector<MyMessage> messages;
    User * user;
};

#endif // COMMUNITY_H

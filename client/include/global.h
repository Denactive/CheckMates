//
// Created by svetlana on 31.05.2021.
//
#ifndef CLIENT_GLOBAL_H
#define CLIENT_GLOBAL_H
#include <string>
#include <mutex>
#include <QString>
#include <QDebug>

// TODO: singletons
//static std::string global_token;
class msg_Singleton
{
public:
    static msg_Singleton& instance()
    {
        static msg_Singleton singleton;
        return singleton;
    }

    std::string& get() {
        qDebug() << "singleton get\n";
        return msg;
    }

    void set(std::string& text) {
        qDebug() << "singleton set to " << QString::fromLocal8Bit(text.c_str()) << "\n";

        std::lock_guard<std::recursive_mutex> locker(mtx_);
        msg = text;
    }

    // Other non-static member functions
private:
    msg_Singleton() {}                                  // Private constructor
    ~msg_Singleton() {}
    msg_Singleton(const msg_Singleton&);                 // Prevent copy-construction
    msg_Singleton& operator=(const msg_Singleton&);      // Prevent assignment
    std::string msg;
    std::recursive_mutex mtx_;
};

#endif //CLIENT_GLOBAL_H

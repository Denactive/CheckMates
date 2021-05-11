#include "include/community.h"

User::User(QString name, int nrating, std::string npassword, std::string nlogin, int ntime)
    :name(name), rating(nrating), password(npassword), login(nlogin), time(ntime)
{
    photo.load("../img/userPhoto.png");
}

#include "include/community.h"

User::User(QString name, int nrating, QString npassword, QString nlogin, QPixmap photo, int ntime)
    :name(name), rating(nrating), password(npassword), login(nlogin), photo(photo), time(ntime)
{

}

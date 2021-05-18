#include "include/community.h"

User::User(QString name, int nrating, QString npassword, QString nlogin, QString photopath, int ntime)
    :name(name), rating(nrating), password(npassword), login(nlogin), time(ntime)
{
    if (!photo.load(photopath)) qDebug() << "User photo not load";
}

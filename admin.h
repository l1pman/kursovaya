#ifndef ADMIN_H
#define ADMIN_H

#include <QString>

#include <user.h>

class Admin : public User
{
public:
    Admin();
    Admin(QString login, QString password, QString role);
};

#endif // ADMIN_H

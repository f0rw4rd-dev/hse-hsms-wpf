#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User();

    static bool isUserExist(QString login);
    static bool areCredentialsCorrect(QString login, QString password);

    static void updateLastVisitDate(QString login);
};

#endif // USER_H

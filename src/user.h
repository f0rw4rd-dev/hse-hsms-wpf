#ifndef USER_H
#define USER_H

#include "group.h"

#include <QString>
#include <QScopedPointer>
#include <QSharedPointer>
#include <pqxx/pqxx>

struct DBUser
{
    DBUser() {};
    DBUser(int id, qint64 registrationDate, qint64 lastVisitDate, int groupId, QString groupName)
        : id(id), registrationDate(registrationDate), lastVisitDate(lastVisitDate)
    {
        group.reset(new DBGroup(groupId, groupName));
    };

    int id;
    qint64 registrationDate;
    qint64 lastVisitDate;

    QScopedPointer<DBGroup> group;
};

class User
{
public:
    User();

    static QString getEncryptedPassword(QString password);

    static bool doesUserExist(int id);
    static bool areCredentialsCorrect(QString login, QString password);

    static void updateLastVisitDate(QString login);

    static QVector<QSharedPointer<DBUser>> getUsers();
    static QScopedPointer<DBUser> getUser(int id);
    static void addUser(QString password, int groupId);
    static void setUserPassword(int id, QString newPassword);
    static void setUserGroup(int id, int newGroupId);
    static void deleteUser(int id);
};

#endif // USER_H

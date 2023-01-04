#ifndef USER_H
#define USER_H

#include "group.h"

#include <QString>
#include <pqxx/pqxx>

struct DBUser
{
    DBUser() {};
    DBUser(int id, int64_t registrationDate, int64_t lastVisitDate, int groupId, QString groupName)
        : id(id), registrationDate(registrationDate), lastVisitDate(lastVisitDate)
    {
        group = std::make_unique<DBGroup>(groupId, groupName);
    };

    int id;
    int64_t registrationDate;
    int64_t lastVisitDate;

    std::unique_ptr<DBGroup> group;
};

class User
{
public:
    User();

    static QString getEncryptedPassword(QString password);

    static bool doesUserExist(int id);
    static bool areCredentialsCorrect(QString login, QString password);

    static void updateLastVisitDate(QString login);

    static QVector<std::shared_ptr<DBUser>> getUsers();
    static std::unique_ptr<DBUser> getUser(int id);
    static void addUser(QString password, int groupId);
    static void setUserPassword(int id, QString newPassword);
    static void setUserGroup(int id, int newGroupId);
    static void deleteUser(int id);

    static pqxx::result getGroups();
};

#endif // USER_H

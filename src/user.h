#ifndef USER_H
#define USER_H

#include <QString>

struct DBUser
{
    DBUser() {};
    DBUser(int id, int64_t registrationDate, int64_t lastVisitDate, int groupId, std::string groupName)
        : id(id), registrationDate(registrationDate), lastVisitDate(lastVisitDate), groupId(groupId), groupName(groupName) {};

    int id;
    int64_t registrationDate;
    int64_t lastVisitDate;
    int groupId;
    std::string groupName;
};

class User
{
public:
    User();

    static bool isUserExist(QString login);
    static bool areCredentialsCorrect(QString login, QString password);

    static void updateLastVisitDate(QString login);

    static QVector<std::shared_ptr<DBUser>> getUsers();
    //static std::unique_ptr<DBUser> getUser(int id);
    static void addUser(DBUser &dbUser);
    static void editPasswordUser(int id, QString newPassword);
    static void editGroupUser(int id, int newGroupId);
    static void deleteUser(int id);
};

#endif // USER_H

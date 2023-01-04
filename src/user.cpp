#include "user.h"
#include "dbconnection.h"

#include <QCryptographicHash>
#include <QDateTime>

User::User()
{

}

QString User::getEncryptedPassword(QString password)
{
    return QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();
}

bool User::areCredentialsCorrect(QString login, QString password)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("SELECT id FROM users WHERE id = '%1' AND password = '%2';").arg(login, getEncryptedPassword(password));

    pqxx::result users = dbConnection->getTransaction()->exec(request.toStdString());

    return users.size() == 1;
}

void User::updateLastVisitDate(QString login)
{
    dbConnection->assertConnectionIsReliable();

    QString timestamp = QString::number(QDateTime::currentSecsSinceEpoch()),
            request = QString("UPDATE users "
                              "SET last_visit_date = '%1' "
                              "WHERE id = '%2';").arg(timestamp, login);

    dbConnection->getTransaction()->exec(request.toStdString());
    dbConnection->getTransaction()->commit();
}

QVector<std::shared_ptr<DBUser>> User::getUsers()
{
    dbConnection->assertConnectionIsReliable();

    QString request = "SELECT users.id, users.registration_date, users.last_visit_date, users.group_id, groups.name FROM users "
                              "LEFT JOIN groups ON users.group_id = groups.id ORDER BY users.id DESC;";

    QVector<std::shared_ptr<DBUser>> users;

    for (auto &[id, registrationDate, lastVisitDate, groupId, groupName] : dbConnection->getTransaction()->query<int, int64_t, int64_t, int, std::string>(request.toStdString()))
        users.append(std::make_shared<DBUser>(id, registrationDate, lastVisitDate, groupId, QString::fromStdString(groupName)));

    return users;
}

std::unique_ptr<DBUser> User::getUser(int id)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("SELECT users.id, users.registration_date, users.last_visit_date, users.group_id, groups.name FROM users "
                              "LEFT JOIN groups ON users.group_id = groups.id WHERE users.id = '%1';").arg(QString::number(id));

    pqxx::result component = dbConnection->getTransaction()->exec(request.toStdString());

    if (component.empty())
        return nullptr;

    pqxx::row row = component[0];

    return std::make_unique<DBUser>(row[0].as<int>(), row[1].as<int64_t>(), row[2].as<int64_t>(), row[3].as<int>(), QString::fromStdString(row[4].as<std::string>()));
}

void User::addUser(QString password, int groupId)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("INSERT INTO users (password, registration_date, group_id) VALUES ('%1', '%2', '%3');")
            .arg(password, QString::number(QDateTime::currentSecsSinceEpoch()), QString::number(groupId));

    dbConnection->getTransaction()->exec(request.toStdString());
    dbConnection->getTransaction()->commit();
}

void User::setUserPassword(int id, QString newPassword)
{
    dbConnection->assertConnectionIsReliable();

    QString newEncryptedPassword = QCryptographicHash::hash(newPassword.toUtf8(), QCryptographicHash::Sha256).toHex(),
            request = QString("UPDATE users SET password = '%1' WHERE id = '%2';")
            .arg(newEncryptedPassword, QString::number(id));

    dbConnection->getTransaction()->exec(request.toStdString());
    dbConnection->getTransaction()->commit();
}

void User::setUserGroup(int id, int newGroupId)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("UPDATE users SET group_id = '%1' WHERE id = '%2';")
            .arg(QString::number(newGroupId), QString::number(id));

    dbConnection->getTransaction()->exec(request.toStdString());
    dbConnection->getTransaction()->commit();
}

void User::deleteUser(int id)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("DELETE FROM users WHERE id = '%1'").arg(id);

    dbConnection->getTransaction()->exec(request.toStdString());
    dbConnection->getTransaction()->commit();
}

bool User::doesUserExist(int id)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("SELECT * FROM users WHERE id = '%1'").arg(QString::number(id));

    pqxx::result result = dbConnection->getTransaction()->exec(request.toStdString());

    return result.size() != 0;
}

pqxx::result User::getGroups()
{
    dbConnection->assertConnectionIsReliable();

    QString request = "SELECT * FROM groups;";

    return dbConnection->getTransaction()->exec(request.toStdString());
}

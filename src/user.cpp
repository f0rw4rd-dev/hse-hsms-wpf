#include "user.h"

#include "dbconnection.h"

#include <QCryptographicHash>
#include <QDateTime>

User::User()
{

}

bool User::isUserExist(QString login)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("SELECT id "
                              "FROM users "
                              "WHERE id = '%1';").arg(login);

    pqxx::result users = dbConnection->getTransaction()->exec(request.toStdString());

    return users.size() == 1;
}

bool User::areCredentialsCorrect(QString login, QString password)
{
    dbConnection->assertConnectionIsReliable();

    QString encryptedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex(),
            request = QString("SELECT id "
                              "FROM users "
                              "WHERE id = '%1' AND password = '%2';").arg(login, encryptedPassword);

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

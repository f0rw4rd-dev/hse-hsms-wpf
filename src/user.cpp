#include "user.h"

#include "dbconnection.h"

#include <QCryptographicHash>
#include <QDateTime>

User::User()
{

}

bool User::isUserExist(QString login)
{
    if (!dbConnection->isConnectionReliable()) {
        //todo handle
        return false;
    }

    QString request = QString("SELECT id "
                              "FROM users "
                              "WHERE id = '%1';").arg(login);

    pqxx::result users = dbConnection->getTransaction()->exec(request.toStdString());

    return users.size() == 1;
}

bool User::areCredentialsCorrect(QString login, QString password)
{
    if (!dbConnection->isConnectionReliable()) {
        //todo handle
        return false;
    }

    QString encryptedPassword = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex();

    QString request = QString("SELECT id "
                              "FROM users "
                              "WHERE id = '%1' AND password = '%2';").arg(login, encryptedPassword);

    pqxx::result users = dbConnection->getTransaction()->exec(request.toStdString());

    return users.size() == 1;
}

void User::updateLastVisitDate(QString login)
{
    if (!dbConnection->isConnectionReliable()) {
        //todo handle
        return;
    }

    QString timestamp = QString::number(QDateTime::currentSecsSinceEpoch());

    QString request = QString("UPDATE users "
                              "SET last_visit_date = '%1' "
                              "WHERE id = '%2';").arg(timestamp, login);

    dbConnection->getTransaction()->exec(request.toStdString());
}

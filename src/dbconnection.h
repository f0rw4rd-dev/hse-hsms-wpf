#ifndef DBCONNECTION_H
#define DBCONNECTION_H

#include <QString>

#include <pqxx/pqxx>

class DBConnection
{
public:
    DBConnection(QString username, QString password, QString address, QString port, QString database);

    bool isConnectionReliable();

    void assertConnectionIsReliable();

    std::unique_ptr<pqxx::connection> &getConnection() { return _connection; };
    std::unique_ptr<pqxx::work> &getTransaction() { return _transaction; };

private:
    void establishConnection(QString data);

private:
    std::unique_ptr<pqxx::connection> _connection;
    std::unique_ptr<pqxx::work> _transaction;
};

extern DBConnection *dbConnection;

#endif // DBCONNECTION_H

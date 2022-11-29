#include "dbconnection.h"

DBConnection::DBConnection(QString username, QString password, QString address, QString port, QString database)
{
    QString data = QString("postgresql://%1:%2@%3:%4/%5").arg(username, password, address, port, database);
    establishConnection(data);
}

bool DBConnection::isConnectionReliable()
{
    if (_connection == nullptr || _transaction == nullptr)
        return false;

    try {
        _transaction->exec("");
    }
    catch (std::exception const &e) {
        return false;
    }

    return true;
}

void DBConnection::establishConnection(QString data)
{
    try {
        _connection = std::make_unique<pqxx::connection>(data.toStdString());
        _transaction = std::make_unique<pqxx::work>(*_connection);
    }
    catch (std::exception const &e) {}
}

DBConnection *dbConnection = nullptr;

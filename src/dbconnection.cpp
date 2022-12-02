#include "dbconnection.h"

#include <QMessageBox>
#include <QApplication>
#include <QThread>

DBConnection::DBConnection(QString username, QString password, QString address, QString port, QString database)
{
    QString data = QString("postgresql://%1:%2@%3:%4/%5").arg(username, password, address, port, database);
    establishConnection(data);
}

bool DBConnection::isConnectionReliable()
{
    if (_connection == nullptr || _transaction == nullptr)
        return false;

    bool isReliable = false;

    for (int i = 0; i < 5; i++) {
        try {
            _transaction->exec("");
        }
        catch (std::exception const) {
            _transaction = std::make_unique<pqxx::work>(*_connection);
            //QThread::sleep(1);
            continue;
        }

        isReliable = true;
        break;
    }

    return isReliable;
}

void DBConnection::assertConnectionIsReliable()
{
    if (!dbConnection->isConnectionReliable()) {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось получить доступ к базе данных!");
        QApplication::quit();
    }
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

#ifndef CONNECTION_H
#define CONNECTION_H

#include <QString>
#include <pqxx/pqxx>

struct Connection
{
    Connection(QString user, QString password, QString database, QString hostAddress, QString port)
    {
        c =
    }

    //pqxx::connection c("user=admin hostaddr=185.251.91.109 port=5432 password=b5gXN6NNeS2JO8Ug dbname=hardware_store");
    pqxx::connection c;
    pqxx::work tx{ c };
};

#endif // CONNECTION_H

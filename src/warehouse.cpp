#include "warehouse.h"
#include "dbconnection.h"

#include <QVector>
#include <QDebug>

QString Warehouse::getAddress(Warehouse &dbWarehouse)
{
    return QString("г. %1, ул. %2, д. %3, %4").arg(dbWarehouse.city, dbWarehouse.street, QString::number(dbWarehouse.house),  QString::number(dbWarehouse.zip));
}

QVector<QSharedPointer<Warehouse>> Warehouse::getWarehouses()
{
    dbConnection->assertConnectionIsReliable();

    QString request = "SELECT id, city, street, house, zip FROM warehouses;";

    QVector<QSharedPointer<Warehouse>> warehouses;

    for (auto &[id, city, street, house, zip] : dbConnection->getTransaction()->query<int, std::string, std::string, int, int>(request.toStdString()))
        warehouses.append(QSharedPointer<Warehouse>(new Warehouse(id, QString::fromStdString(city), QString::fromStdString(street), house, zip)));

    return warehouses;
}

QScopedPointer<Warehouse> Warehouse::getWarehouse(int id)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("SELECT id, city, street, house, zip FROM warehouses WHERE id = '%1';").arg(QString::number(id));

    pqxx::result warehouse = dbConnection->getTransaction()->exec(request.toStdString());

    if (warehouse.empty())
        return QScopedPointer<Warehouse>();

    pqxx::row row = warehouse[0];

    return QScopedPointer<Warehouse>(new Warehouse(row[0].as<int>(), QString::fromStdString(row[1].as<std::string>()), QString::fromStdString(row[2].as<std::string>()), row[3].as<int>(), row[4].as<int>()));
}

void Warehouse::addWarehouse(Warehouse &warehouse)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("INSERT INTO warehouses (city, street, house, zip) VALUES ('%1', '%2', '%3', '%4');")
            .arg(warehouse.city, warehouse.street, QString::number(warehouse.house), QString::number(warehouse.zip));

    dbConnection->getTransaction()->exec(request.toStdString());
    dbConnection->getTransaction()->commit();
}

void Warehouse::setWarehouse(Warehouse &warehouse)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("UPDATE warehouses SET city = '%1', street = '%2', house = '%3', zip = '%4' WHERE id = '%5';")
            .arg(warehouse.city, warehouse.street, QString::number(warehouse.house), QString::number(warehouse.zip), QString::number(warehouse.id));

    dbConnection->getTransaction()->exec(request.toStdString());
    dbConnection->getTransaction()->commit();
}

void Warehouse::deleteWarehouse(int id)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("DELETE FROM warehouses WHERE id = '%1';").arg(QString::number(id));

    dbConnection->getTransaction()->exec(request.toStdString());
    dbConnection->getTransaction()->commit();
}

bool Warehouse::doesWarehouseExist(QString city, QString street, int house, int zip)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("SELECT * FROM warehouses WHERE city = '%1' AND street = '%2' AND house = '%3' AND zip = '%4';").arg(city, street, QString::number(house), QString::number(zip));

    pqxx::result result = dbConnection->getTransaction()->exec(request.toStdString());

    return result.size() != 0;
}


bool Warehouse::doesWarehouseExist(int id)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("SELECT * FROM warehouses WHERE id = '%1';").arg(QString::number(id));

    pqxx::result result = dbConnection->getTransaction()->exec(request.toStdString());

    return result.size() != 0;
}

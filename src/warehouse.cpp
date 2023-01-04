#include "warehouse.h"
#include "dbconnection.h"

#include <QVector>
#include <QDebug>

Warehouse::Warehouse()
{

}

QString Warehouse::getAddress(DBWarehouse &dbWarehouse)
{
    return QString("г. %1, ул. %2, д. %3, %4").arg(QString::fromStdString(dbWarehouse.city), QString::fromStdString(dbWarehouse.street), QString::number(dbWarehouse.house),  QString::number(dbWarehouse.zip));
}

QVector<std::shared_ptr<DBWarehouse>> Warehouse::getWarehouses()
{
    dbConnection->assertConnectionIsReliable();

    QString request = "SELECT id, city, street, house, zip FROM warehouses;";

    QVector<std::shared_ptr<DBWarehouse>> warehouses;

    for (auto &[id, city, street, house, zip] : dbConnection->getTransaction()->query<int, std::string, std::string, int, int>(request.toStdString()))
        warehouses.append(std::make_shared<DBWarehouse>(id, city, street, house, zip));

    return warehouses;
}

std::unique_ptr<DBWarehouse> Warehouse::getWarehouse(int id)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("SELECT id, city, street, house, zip FROM warehouses WHERE id = '%1';").arg(QString::number(id));

    pqxx::result warehouse = dbConnection->getTransaction()->exec(request.toStdString());

    if (warehouse.empty())
        return nullptr;

    pqxx::row row = warehouse[0];

    return std::make_unique<DBWarehouse>(row[0].as<int>(), row[1].as<std::string>(), row[2].as<std::string>(), row[3].as<int>(), row[4].as<int>());
}

void Warehouse::addWarehouse(DBWarehouse &dbWarehouse)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("INSERT INTO warehouses (city, street, house, zip) VALUES ('%1', '%2', '%3', '%4');")
            .arg(QString::fromStdString(dbWarehouse.city), QString::fromStdString(dbWarehouse.street), QString::number(dbWarehouse.house), QString::number(dbWarehouse.zip));

    dbConnection->getTransaction()->exec(request.toStdString());
    dbConnection->getTransaction()->commit();
}

void Warehouse::setWarehouse(DBWarehouse &dbWarehouse)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("UPDATE warehouses SET city = '%1', street = '%2', house = '%3', zip = '%4' WHERE id = '%5';")
            .arg(QString::fromStdString(dbWarehouse.city), QString::fromStdString(dbWarehouse.street), QString::number(dbWarehouse.house), QString::number(dbWarehouse.zip), QString::number(dbWarehouse.id));

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

QVector<std::shared_ptr<DBWarehouseComponent>> Warehouse::getWarehouseComponents()
{
    dbConnection->assertConnectionIsReliable();

    QString request = "SELECT warehouses_components.warehouse_id, warehouses.city, warehouses.street, warehouses.house, warehouses.zip, warehouses_components.component_id, components.name, warehouses_components.amount FROM warehouses_components "
                      "LEFT JOIN warehouses ON warehouses_components.warehouse_id = warehouses.id "
                      "LEFT JOIN components ON warehouses_components.component_id = components.id;";

    QVector<std::shared_ptr<DBWarehouseComponent>> components;

    for (auto &[warehouseId, city, street, house, zip, componentId, componentName, amount] : dbConnection->getTransaction()->query<int, std::string, std::string, int, int, int, std::string, int>(request.toStdString()))
        components.append(std::make_shared<DBWarehouseComponent>(warehouseId, city, street, house, zip, componentId, componentName, amount));

    return components;
}

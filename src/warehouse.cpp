#include "warehouse.h"
#include "dbconnection.h"

#include <QVector>

Warehouse::Warehouse()
{

}

QVector<std::shared_ptr<DBWarehouse>> Warehouse::getWarehouses()
{
    dbConnection->assertConnectionIsReliable();

    QString request = "SELECT id, address FROM warehouses;";

    QVector<std::shared_ptr<DBWarehouse>> warehouses;

    for (auto &[id, address] : dbConnection->getTransaction()->query<int, std::string>(request.toStdString()))
        warehouses.append(std::make_shared<DBWarehouse>(id, address));

    return warehouses;
}

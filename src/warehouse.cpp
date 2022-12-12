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

void Warehouse::addWarehouse(DBWarehouse &dbWarehouse)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("INSERT INTO warehouses (address) VALUES ('%1');")
            .arg(QString::fromStdString(dbWarehouse.address));

    dbConnection->getTransaction()->exec(request.toStdString());
    dbConnection->getTransaction()->commit();

    // check on errors (not unique, e.g.)
}

bool Warehouse::doesWarehouseExist(QString address)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("SELECT * FROM warehouses WHERE address = '%1'").arg(address);

    pqxx::result result = dbConnection->getTransaction()->exec(request.toStdString());

    return result.size() != 0;
}


bool Warehouse::doesWarehouseExist(int id)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("SELECT * FROM warehouses WHERE id = '%1'").arg(QString::number(id));

    pqxx::result result = dbConnection->getTransaction()->exec(request.toStdString());

    return result.size() != 0;
}

QVector<std::shared_ptr<DBComponentInWarehouse>> Warehouse::getComponentsInWarehouses()
{
    dbConnection->assertConnectionIsReliable();

    QString request = "SELECT warehouses_components.warehouse_id, warehouses.address, warehouses_components.component_id, components.name, warehouses_components.amount FROM warehouses_components "
                      "LEFT JOIN warehouses ON warehouses_components.warehouse_id = warehouses.id "
                      "LEFT JOIN components ON warehouses_components.component_id = components.id;";

    QVector<std::shared_ptr<DBComponentInWarehouse>> components;

    for (auto &[warehouseId, address, componentId, componentName, amount] : dbConnection->getTransaction()->query<int, std::string, int, std::string, int>(request.toStdString()))
        components.append(std::make_shared<DBComponentInWarehouse>(warehouseId, address, componentId, componentName, amount));

    return components;
}

#include "warehousecomponent.h"
#include "dbconnection.h"

WarehouseComponent::WarehouseComponent()
{

}

QVector<QSharedPointer<DBWarehouseComponent>> WarehouseComponent::getWarehouseComponents()
{
    dbConnection->assertConnectionIsReliable();

    QString request = "SELECT warehouses_components.warehouse_id, warehouses.city, warehouses.street, warehouses.house, warehouses.zip, warehouses_components.component_id, components.name, warehouses_components.amount FROM warehouses_components "
                      "LEFT JOIN warehouses ON warehouses_components.warehouse_id = warehouses.id "
                      "LEFT JOIN components ON warehouses_components.component_id = components.id;";

    QVector<QSharedPointer<DBWarehouseComponent>> warehouseComponents;

    for (auto &[warehouseId, city, street, house, zip, componentId, componentName, amount] : dbConnection->getTransaction()->query<int, std::string, std::string, int, int, int, std::string, int>(request.toStdString()))
        warehouseComponents.append(QSharedPointer<DBWarehouseComponent>(new DBWarehouseComponent(warehouseId, QString::fromStdString(city), QString::fromStdString(street), house, zip, componentId, QString::fromStdString(componentName), amount)));

    return warehouseComponents;
}

QScopedPointer<DBWarehouseComponent> WarehouseComponent::getWarehouseComponent(int componentId, int warehouseId)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("SELECT amount FROM warehouses_components WHERE component_id = '%1' AND warehouse_id = '%2';").arg(QString::number(componentId), QString::number(warehouseId));

    pqxx::result warehouseComponent = dbConnection->getTransaction()->exec(request.toStdString());

    if (warehouseComponent.empty())
        return QScopedPointer<DBWarehouseComponent>();

    pqxx::row row = warehouseComponent[0];

    return QScopedPointer<DBWarehouseComponent>(new DBWarehouseComponent(warehouseId, componentId, row[0].as<int>()));
}

void WarehouseComponent::addWarehouseComponent(DBWarehouseComponent &dbWarehouseComponent)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("INSERT INTO warehouses_components (warehouse_id, component_id, amount) VALUES ('%1', '%2', '%3');")
            .arg(QString::number(dbWarehouseComponent.warehouse->id), QString::number(dbWarehouseComponent.component->id), QString::number(dbWarehouseComponent.amount));

    dbConnection->getTransaction()->exec(request.toStdString());
    dbConnection->getTransaction()->commit();
}

void WarehouseComponent::setWarehouseComponent(DBWarehouseComponent &dbWarehouseComponent)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("UPDATE warehouses_components SET amount = '%1' WHERE warehouse_id = '%2' AND component_id = '%3';")
            .arg(QString::number(dbWarehouseComponent.amount), QString::number(dbWarehouseComponent.warehouse->id), QString::number(dbWarehouseComponent.component->id));

    dbConnection->getTransaction()->exec(request.toStdString());
    dbConnection->getTransaction()->commit();
}

void WarehouseComponent::deleteWarehouseComponent(int componentId, int warehouseId)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("DELETE FROM warehouses_components WHERE component_id = '%1' AND warehouse_id = '%2';").arg(QString::number(componentId), QString::number(warehouseId));

    dbConnection->getTransaction()->exec(request.toStdString());
    dbConnection->getTransaction()->commit();
}

bool WarehouseComponent::doesWarehouseComponentExist(int componentId, int warehouseId)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("SELECT * FROM warehouses_components WHERE component_id = '%1' AND warehouse_id = '%2';").arg(QString::number(componentId), QString::number(warehouseId));

    pqxx::result result = dbConnection->getTransaction()->exec(request.toStdString());

    return result.size() != 0;
}

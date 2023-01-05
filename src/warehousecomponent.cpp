#include "warehousecomponent.h"
#include "dbconnection.h"

QVector<QSharedPointer<WarehouseComponent>> WarehouseComponent::getWarehouseComponents()
{
    dbConnection->assertConnectionIsReliable();

    QString request = "SELECT warehouses_components.warehouse_id, warehouses.city, warehouses.street, warehouses.house, warehouses.zip, warehouses_components.component_id, components.name, warehouses_components.amount FROM warehouses_components "
                      "LEFT JOIN warehouses ON warehouses_components.warehouse_id = warehouses.id "
                      "LEFT JOIN components ON warehouses_components.component_id = components.id;";

    QVector<QSharedPointer<WarehouseComponent>> warehouseComponents;

    for (auto &[warehouseId, city, street, house, zip, componentId, componentName, amount] : dbConnection->getTransaction()->query<int, std::string, std::string, int, int, int, std::string, int>(request.toStdString()))
        warehouseComponents.append(QSharedPointer<WarehouseComponent>(new WarehouseComponent(warehouseId, QString::fromStdString(city), QString::fromStdString(street), house, zip, componentId, QString::fromStdString(componentName), amount)));

    return warehouseComponents;
}

QScopedPointer<WarehouseComponent> WarehouseComponent::getWarehouseComponent(int componentId, int warehouseId)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("SELECT amount FROM warehouses_components WHERE component_id = '%1' AND warehouse_id = '%2';").arg(QString::number(componentId), QString::number(warehouseId));

    pqxx::result warehouseComponent = dbConnection->getTransaction()->exec(request.toStdString());

    if (warehouseComponent.empty())
        return QScopedPointer<WarehouseComponent>();

    pqxx::row row = warehouseComponent[0];

    return QScopedPointer<WarehouseComponent>(new WarehouseComponent(warehouseId, componentId, row[0].as<int>()));
}

void WarehouseComponent::addWarehouseComponent(WarehouseComponent &warehouseComponent)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("INSERT INTO warehouses_components (warehouse_id, component_id, amount) VALUES ('%1', '%2', '%3');")
            .arg(QString::number(warehouseComponent.warehouse->id), QString::number(warehouseComponent.component->id), QString::number(warehouseComponent.amount));

    dbConnection->getTransaction()->exec(request.toStdString());
    dbConnection->getTransaction()->commit();
}

void WarehouseComponent::setWarehouseComponent(WarehouseComponent &warehouseComponent)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("UPDATE warehouses_components SET amount = '%1' WHERE warehouse_id = '%2' AND component_id = '%3';")
            .arg(QString::number(warehouseComponent.amount), QString::number(warehouseComponent.warehouse->id), QString::number(warehouseComponent.component->id));

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

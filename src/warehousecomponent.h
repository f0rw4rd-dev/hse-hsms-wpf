#ifndef WAREHOUSECOMPONENT_H
#define WAREHOUSECOMPONENT_H

#include "warehouse.h"

struct DBWarehouseComponent
{
    DBWarehouseComponent() {};
    DBWarehouseComponent(int warehouseId, int componentId, int amount)
        : amount(amount)
    {
        warehouse.reset(new DBWarehouse(warehouseId));
        component.reset(new DBComponent(componentId));
    };

    DBWarehouseComponent(int warehouseId, QString city, QString street, int house, int zip, int componentId, QString componentName, int amount)
        : amount(amount)
    {
        warehouse.reset(new DBWarehouse(warehouseId, city, street, house, zip));
        component.reset(new DBComponent(componentId, componentName));
    };

    QScopedPointer<DBWarehouse> warehouse;
    QScopedPointer<DBComponent> component;
    int amount;
};

class WarehouseComponent
{
public:
    WarehouseComponent();

    static QVector<QSharedPointer<DBWarehouseComponent>> getWarehouseComponents();
    static QScopedPointer<DBWarehouseComponent> getWarehouseComponent(int componentId, int warehouseId);
    static void addWarehouseComponent(DBWarehouseComponent &dbWarehouseComponent);
    static void setWarehouseComponent(DBWarehouseComponent &dbWarehouseComponent);
    static void deleteWarehouseComponent(int componentId, int warehouseId);
    static bool doesWarehouseComponentExist(int componentId, int warehouseId);
};

#endif // WAREHOUSECOMPONENT_H

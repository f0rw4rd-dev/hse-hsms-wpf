#ifndef WAREHOUSECOMPONENT_H
#define WAREHOUSECOMPONENT_H

#include "warehouse.h"
#include "component.h"

class WarehouseComponent
{
public:
    WarehouseComponent() {};
    WarehouseComponent(int warehouseId, int componentId, int amount)
        : amount(amount)
    {
        warehouse.reset(new Warehouse(warehouseId));
        component.reset(new Component(componentId));
    };

    WarehouseComponent(int warehouseId, QString city, QString street, int house, int zip, int componentId, QString componentName, int amount)
        : amount(amount)
    {
        warehouse.reset(new Warehouse(warehouseId, city, street, house, zip));
        component.reset(new Component(componentId, componentName));
    };

    static QVector<QSharedPointer<WarehouseComponent>> getWarehouseComponents();
    static QScopedPointer<WarehouseComponent> getWarehouseComponent(int componentId, int warehouseId);
    static void addWarehouseComponent(WarehouseComponent &warehouseComponent);
    static void setWarehouseComponent(WarehouseComponent &warehouseComponent);
    static void deleteWarehouseComponent(int componentId, int warehouseId);
    static bool doesWarehouseComponentExist(int componentId, int warehouseId);

public:
    QScopedPointer<Warehouse> warehouse;
    QScopedPointer<Component> component;
    int amount;
};

#endif // WAREHOUSECOMPONENT_H

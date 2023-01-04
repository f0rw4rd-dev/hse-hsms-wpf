#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "component.h"

#include <QString>
#include <QScopedPointer>
#include <QSharedPointer>

struct DBWarehouse
{
    DBWarehouse() {};
    DBWarehouse(QString city, QString street, int house, int zip)
        : city(city), street(street), house(house), zip(zip) {};
    DBWarehouse(int id, QString city, QString street, int house, int zip)
        : id(id), city(city), street(street), house(house), zip(zip) {};

    int id;
    QString city;
    QString street;
    int house;
    int zip;
};

struct DBWarehouseComponent
{
    DBWarehouseComponent() {};

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

class Warehouse
{
public:
    Warehouse();

    static QString getAddress(DBWarehouse &dbWarehouse);

    static QVector<QSharedPointer<DBWarehouse>> getWarehouses();
    static QScopedPointer<DBWarehouse> getWarehouse(int id);
    static void addWarehouse(DBWarehouse &dbWarehouse);
    static void setWarehouse(DBWarehouse &dbWarehouse);
    static void deleteWarehouse(int id);
    static bool doesWarehouseExist(QString city, QString street, int house, int zip);
    static bool doesWarehouseExist(int id);

    static QVector<QSharedPointer<DBWarehouseComponent>> getWarehouseComponents();
};

#endif // WAREHOUSE_H

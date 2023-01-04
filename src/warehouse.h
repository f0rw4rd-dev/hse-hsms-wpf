#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "component.h"

#include <QString>

struct DBWarehouse
{
    DBWarehouse() {};
    DBWarehouse(std::string city, std::string street, int house, int zip)
        : city(city), street(street), house(house), zip(zip) {};
    DBWarehouse(int id, std::string city, std::string street, int house, int zip)
        : id(id), city(city), street(street), house(house), zip(zip) {};

    int id;
    std::string city;
    std::string street;
    int house;
    int zip;
};

struct DBWarehouseComponent
{
    DBWarehouseComponent() {};

    DBWarehouseComponent(int warehouseId, std::string city, std::string street, int house, int zip, int componentId, std::string componentName, int amount)
        : amount(amount)
    {
        warehouse = std::make_unique<DBWarehouse>(warehouseId, city, street, house, zip);
        component = std::make_unique<DBComponent>(componentId, componentName);
    };

    std::unique_ptr<DBWarehouse> warehouse;
    std::unique_ptr<DBComponent> component;
    int amount;
};

class Warehouse
{
public:
    Warehouse();

    static QString getAddress(DBWarehouse &dbWarehouse);

    static QVector<std::shared_ptr<DBWarehouse>> getWarehouses();
    static std::unique_ptr<DBWarehouse> getWarehouse(int id);
    static void addWarehouse(DBWarehouse &dbWarehouse);
    static void setWarehouse(DBWarehouse &dbWarehouse);
    static void deleteWarehouse(int id);
    static bool doesWarehouseExist(QString city, QString street, int house, int zip);
    static bool doesWarehouseExist(int id);

    static QVector<std::shared_ptr<DBWarehouseComponent>> getWarehouseComponents();
};

#endif // WAREHOUSE_H

#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <QString>

struct DBWarehouse
{
    DBWarehouse() {};
    DBWarehouse(int id, std::string address)
        : id(id), address(address) {};

    int id;
    std::string address;
};

struct DBComponentInWarehouse
{
    DBComponentInWarehouse() {};
    DBComponentInWarehouse(int warehouseId, std::string address, int componentId, std::string componentName, int amount)
        : warehouseId(warehouseId), address(address), componentId(componentId), componentName(componentName), amount(amount) {};

    int warehouseId;
    std::string address;
    int componentId;
    std::string componentName;
    int amount;
};

class Warehouse
{
public:
    Warehouse();

    static QVector<std::shared_ptr<DBWarehouse>> getWarehouses();
    static void addWarehouse(DBWarehouse &dbWarehouse);

    static bool doesWarehouseExist(QString address);
    static bool doesWarehouseExist(int id);

    static QVector<std::shared_ptr<DBComponentInWarehouse>> getComponentsInWarehouses();
};

#endif // WAREHOUSE_H

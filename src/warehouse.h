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

class Warehouse
{
public:
    Warehouse();

    static QVector<std::shared_ptr<DBWarehouse>> getWarehouses();
};

#endif // WAREHOUSE_H

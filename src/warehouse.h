#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include "component.h"

#include <QString>
#include <QScopedPointer>
#include <QSharedPointer>

struct DBWarehouse
{
    DBWarehouse() {};
    DBWarehouse(int id) : id(id) {};
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
};

#endif // WAREHOUSE_H

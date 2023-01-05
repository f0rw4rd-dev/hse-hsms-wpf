#ifndef WAREHOUSE_H
#define WAREHOUSE_H

#include <QString>
#include <QScopedPointer>
#include <QSharedPointer>

class Warehouse
{
public:
    Warehouse() {};
    Warehouse(int id) : id(id) {};
    Warehouse(QString city, QString street, int house, int zip)
        : city(city), street(street), house(house), zip(zip) {};
    Warehouse(int id, QString city, QString street, int house, int zip)
        : id(id), city(city), street(street), house(house), zip(zip) {};

    static QString getAddress(Warehouse &warehouse);

    static QVector<QSharedPointer<Warehouse>> getWarehouses();
    static QScopedPointer<Warehouse> getWarehouse(int id);
    static void addWarehouse(Warehouse &warehouse);
    static void setWarehouse(Warehouse &warehouse);
    static void deleteWarehouse(int id);
    static bool doesWarehouseExist(QString city, QString street, int house, int zip);
    static bool doesWarehouseExist(int id);

public:
    int id;
    QString city;
    QString street;
    int house;
    int zip;
};

#endif // WAREHOUSE_H

#ifndef COMPONENT_H
#define COMPONENT_H

#include "componenttype.h"

#include <QVector>
#include <QScopedPointer>
#include <QSharedPointer>
#include <pqxx/pqxx>

struct DBComponent
{
    DBComponent() {};
    DBComponent(int id) : id(id) {};
    DBComponent(int id, QString name, int typeId, QString typeName, int warranty, float price)
        : id(id), name(name), warranty(warranty), price(price)
    {
        componentType.reset(new DBComponentType(typeId, typeName));
    };
    DBComponent(QString name, int typeId, QString typeName, int warranty, float price)
        : name(name), warranty(warranty), price(price)
    {
        componentType.reset(new DBComponentType(typeId, typeName));
    };
    DBComponent(int id, QString name) : id(id), name(name) {};

    int id;
    QString name;
    QScopedPointer<DBComponentType> componentType;
    int warranty; // in months
    float price; // in RUB
};

class Component
{
public:
    Component();

    static QVector<QSharedPointer<DBComponent>> getComponents();
    static QScopedPointer<DBComponent> getComponent(int id);
    static void addComponent(DBComponent &dbComponent);
    static void setComponent(DBComponent &dbComponent);
    static void deleteComponent(int id);

    static bool doesComponentExist(QString name);
    static bool doesComponentExist(int id);
};

#endif // COMPONENT_H

#ifndef COMPONENT_H
#define COMPONENT_H

#include "componenttype.h"

#include <QVector>
#include <QScopedPointer>
#include <QSharedPointer>
#include <pqxx/pqxx>

class Component
{
public:
    Component() {};
    Component(int id) : id(id) {};
    Component(int id, QString name, int typeId, QString typeName, int warranty, float price)
        : id(id), name(name), warranty(warranty), price(price)
    {
        componentType.reset(new ComponentType(typeId, typeName));
    };
    Component(QString name, int typeId, QString typeName, int warranty, float price)
        : name(name), warranty(warranty), price(price)
    {
        componentType.reset(new ComponentType(typeId, typeName));
    };
    Component(int id, QString name) : id(id), name(name) {};
    Component(int id, QString name, int amount) : id(id), name(name), amount(amount) {};

    static QVector<QSharedPointer<Component>> getComponents();
    static QSharedPointer<Component> getComponent(int id);
    static void addComponent(Component &component);
    static void setComponent(Component &component);
    static void deleteComponent(int id);

    static bool doesComponentExist(QString name);
    static bool doesComponentExist(int id);

public:
    int id;
    QString name;
    QScopedPointer<ComponentType> componentType;
    int warranty;
    float price;

    int amount; // only for special components (e.g. ram) as part of computers
};

#endif // COMPONENT_H

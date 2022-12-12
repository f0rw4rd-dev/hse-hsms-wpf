#ifndef COMPONENT_H
#define COMPONENT_H

#include <QVector>
#include <string>
#include <pqxx/pqxx>

struct DBComponent
{
    DBComponent() {};
    DBComponent(int id, std::string name, int typeId, std::string typeName, int warranty, float price)
        : id(id), name(name), typeId(typeId), typeName(typeName), warranty(warranty), price(price) {};

    int id;
    std::string name;
    int typeId;
    std::string typeName;
    int warranty; // in months
    float price; // in RUB
};

class Component
{
public:
    Component();

    static QVector<std::shared_ptr<DBComponent>> getComponents();
    static std::unique_ptr<DBComponent> getComponent(int id);
    static void addComponent(DBComponent &dbComponent);
    static void setComponent(DBComponent &dbComponent);
    static void deleteComponent(int id);

    static bool doesComponentExist(QString name);
    static bool doesComponentExist(int id);

    static pqxx::result getComponentTypes();
};

#endif // COMPONENT_H

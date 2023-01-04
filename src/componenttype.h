#ifndef COMPONENTTYPE_H
#define COMPONENTTYPE_H

#include <QString>

struct DBComponentType
{
    DBComponentType() {};
    DBComponentType(int id, QString name) : id(id), name(name) {};

    int id;
    QString name;
};

class ComponentType
{
public:
    ComponentType();
};

#endif // COMPONENTTYPE_H

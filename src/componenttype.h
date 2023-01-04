#ifndef COMPONENTTYPE_H
#define COMPONENTTYPE_H

#include <QString>
#include <QSharedPointer>

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

    static QVector<QSharedPointer<DBComponentType>> getComponentTypes();
};

#endif // COMPONENTTYPE_H

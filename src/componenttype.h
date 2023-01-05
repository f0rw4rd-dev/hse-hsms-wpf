#ifndef COMPONENTTYPE_H
#define COMPONENTTYPE_H

#include <QString>
#include <QSharedPointer>

class ComponentType
{
public:
    ComponentType() {};
    ComponentType(int id, QString name) : id(id), name(name) {};

    static QVector<QSharedPointer<ComponentType>> getComponentTypes();

public:
    int id;
    QString name;
};

#endif // COMPONENTTYPE_H

#ifndef CHARACTERISTIC_H
#define CHARACTERISTIC_H

#include "component.h"

#include <QVector>
#include <QSharedPointer>

struct DBCharacteristic
{
    DBCharacteristic() {};
    DBCharacteristic(int id, int componentId, int characteristicTypeId, QString characteristicTypeName, QString value)
        : id(id), componentId(componentId), characteristicTypeId(characteristicTypeId), characteristicTypeName(characteristicTypeName), value(value)
    {
        componentName = Component::getComponent(componentId)->name;
    };

    int id;
    int componentId;
    QString componentName;
    int characteristicTypeId;
    QString characteristicTypeName;
    QString value;
};

class Characteristic
{
public:
    Characteristic();

    static QVector<QSharedPointer<DBCharacteristic>> getCharacteristics();
};

#endif // CHARACTERISTICS_H

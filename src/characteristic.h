#ifndef CHARACTERISTIC_H
#define CHARACTERISTIC_H

#include "component.h"

#include <QVector>
#include <string>

struct DBCharacteristic
{
    DBCharacteristic() {};
    DBCharacteristic(int id, int componentId, int characteristicTypeId, std::string characteristicTypeName, std::string value) : id(id), componentId(componentId), characteristicTypeId(characteristicTypeId), characteristicTypeName(characteristicTypeName), value(value)
    {
        componentName = Component::getComponent(componentId)->name;
    };

    int id;
    int componentId;
    std::string componentName;
    int characteristicTypeId;
    std::string characteristicTypeName;
    std::string value;
};

class Characteristic
{
public:
    Characteristic();

    static QVector<std::shared_ptr<DBCharacteristic>> getCharacteristics();
};

#endif // CHARACTERISTICS_H

#include "characteristic.h"
#include "dbconnection.h"

Characteristic::Characteristic()
{

}

QVector<std::shared_ptr<DBCharacteristic>> Characteristic::getCharacteristics()
{
    dbConnection->assertConnectionIsReliable();

    QString request = "SELECT components_characteristics.id, components_characteristics.characteristic_type_id, components_characteristics.value, components_characteristics.component_id, characteristics_types.name FROM components_characteristics "
                              "LEFT JOIN characteristics_types ON components_characteristics.characteristic_type_id = characteristics_types.id;";

    QVector<std::shared_ptr<DBCharacteristic>> characteristics;

    for (auto &[id, characteristicTypeId, value, componentId, characteristicTypeName] : dbConnection->getTransaction()->query<int, int, std::string, int, std::string>(request.toStdString()))
        characteristics.append(std::make_shared<DBCharacteristic>(id, componentId, characteristicTypeId, QString::fromStdString(characteristicTypeName), QString::fromStdString(value)));

    return characteristics;
}

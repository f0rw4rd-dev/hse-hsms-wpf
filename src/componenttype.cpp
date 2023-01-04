#include "componenttype.h"
#include "dbconnection.h"

#include <QList>

ComponentType::ComponentType()
{

}

QVector<QSharedPointer<DBComponentType>> ComponentType::getComponentTypes()
{
    dbConnection->assertConnectionIsReliable();

    QString request = "SELECT id, name FROM components_types;";

    QVector<QSharedPointer<DBComponentType>> componentTypes;

    for (auto &[id, name] : dbConnection->getTransaction()->query<int, std::string>(request.toStdString()))
        componentTypes.append(QSharedPointer<DBComponentType>(new DBComponentType(id, QString::fromStdString(name))));

    return componentTypes;
}

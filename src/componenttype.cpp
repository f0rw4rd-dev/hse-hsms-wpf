#include "componenttype.h"
#include "dbconnection.h"

#include <QList>

QVector<QSharedPointer<ComponentType>> ComponentType::getComponentTypes()
{
    dbConnection->assertConnectionIsReliable();

    QString request = "SELECT id, name FROM components_types;";

    QVector<QSharedPointer<ComponentType>> componentTypes;

    for (auto &[id, name] : dbConnection->getTransaction()->query<int, std::string>(request.toStdString()))
        componentTypes.append(QSharedPointer<ComponentType>(new ComponentType(id, QString::fromStdString(name))));

    return componentTypes;
}

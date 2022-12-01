#include "component.h"

#include "dbconnection.h"

Component::Component()
{

}

QVector<std::shared_ptr<DBComponent>> Component::getComponents()
{
    dbConnection->assertConnectionIsReliable();

    QString request = "SELECT components.id, components.name, components_types.id, components_types.name, components.warranty, components.price FROM components "
                              "LEFT JOIN components_types ON components.component_type_id = components_types.id;";

    QVector<std::shared_ptr<DBComponent>> components;

    for (auto &[id, name, typeId, typeName, warranty, price] : dbConnection->getTransaction()->query<int, std::string, int, std::string, int, float>(request.toStdString()))
        components.append(std::make_shared<DBComponent>(id, name, typeId, typeName, warranty, price));

    return components;
}

void Component::addComponent(DBComponent &dbComponent)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("INSERT INTO components (component_type_id, name, warranty, price) VALUES ('%1', '%2', '%3', '%4');")
            .arg(QString::number(dbComponent.typeId), QString::fromStdString(dbComponent.name), QString::number(dbComponent.warranty), QString::number(dbComponent.price));

    dbConnection->getTransaction()->exec(request.toStdString());
    dbConnection->getTransaction()->commit();

    // check on errors (not unique, e.g.)
}

void Component::setComponent()
{

}

void Component::deleteComponent(int id)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("DELETE FROM components WHERE id = '%1'").arg(id);

    dbConnection->getTransaction()->exec(request.toStdString());
    //dbConnection->getTransaction()->commit();
}

pqxx::result Component::getComponentTypes()
{
    dbConnection->assertConnectionIsReliable();

    QString request = "SELECT * FROM components_types;";

    return dbConnection->getTransaction()->exec(request.toStdString());
}

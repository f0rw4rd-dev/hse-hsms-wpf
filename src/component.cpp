#include "component.h"
#include "dbconnection.h"

#include <QDebug>

Component::Component()
{

}

QVector<std::shared_ptr<DBComponent>> Component::getComponents()
{
    dbConnection->assertConnectionIsReliable();

    QString request = "SELECT components.id, components.name, components_types.id, components_types.name, components.warranty, components.price FROM components "
                              "LEFT JOIN components_types ON components.component_type_id = components_types.id ORDER BY components.id DESC;";

    QVector<std::shared_ptr<DBComponent>> components;

    for (auto &[id, name, typeId, typeName, warranty, price] : dbConnection->getTransaction()->query<int, std::string, int, std::string, int, float>(request.toStdString()))
        components.append(std::make_shared<DBComponent>(id, QString::fromStdString(name), typeId, QString::fromStdString(typeName), warranty, price));

    return components;
}

std::unique_ptr<DBComponent> Component::getComponent(int id)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("SELECT components.id, components.name, components_types.id, components_types.name, components.warranty, components.price FROM components "
                              "LEFT JOIN components_types ON components.component_type_id = components_types.id WHERE components.id = '%1';").arg(QString::number(id));

    pqxx::result component = dbConnection->getTransaction()->exec(request.toStdString());

    if (component.empty())
        return nullptr;

    pqxx::row row = component[0];

    return std::make_unique<DBComponent>(row[0].as<int>(), QString::fromStdString(row[1].as<std::string>()), row[2].as<int>(), QString::fromStdString(row[3].as<std::string>()), row[4].as<int>(), row[5].as<float>());
}

void Component::addComponent(DBComponent &dbComponent)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("INSERT INTO components (component_type_id, name, warranty, price) VALUES ('%1', '%2', '%3', '%4');")
            .arg(QString::number(dbComponent.componentType->id), dbComponent.name, QString::number(dbComponent.warranty), QString::number(dbComponent.price));

    dbConnection->getTransaction()->exec(request.toStdString());
    dbConnection->getTransaction()->commit();

    // check on errors (not unique, e.g.)
}

void Component::setComponent(DBComponent &dbComponent)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("UPDATE components SET component_type_id = '%1', name = '%2', warranty = '%3', price = '%4' WHERE id = '%5';")
            .arg(QString::number(dbComponent.componentType->id), dbComponent.name, QString::number(dbComponent.warranty), QString::number(dbComponent.price), QString::number(dbComponent.id));

    dbConnection->getTransaction()->exec(request.toStdString());
    dbConnection->getTransaction()->commit();
}

void Component::deleteComponent(int id)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("DELETE FROM components WHERE id = '%1'").arg(QString::number(id));

    dbConnection->getTransaction()->exec(request.toStdString());
    dbConnection->getTransaction()->commit();
}

bool Component::doesComponentExist(QString name)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("SELECT * FROM components WHERE name = '%1'").arg(name);

    pqxx::result result = dbConnection->getTransaction()->exec(request.toStdString());

    return result.size() != 0;
}

bool Component::doesComponentExist(int id)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("SELECT * FROM components WHERE id = '%1'").arg(QString::number(id));

    pqxx::result result = dbConnection->getTransaction()->exec(request.toStdString());

    return result.size() != 0;
}

pqxx::result Component::getComponentTypes()
{
    dbConnection->assertConnectionIsReliable();

    QString request = "SELECT * FROM components_types;";

    return dbConnection->getTransaction()->exec(request.toStdString());
}

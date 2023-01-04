#include "group.h"
#include "dbconnection.h"

#include <QList>

Group::Group()
{

}

QVector<std::shared_ptr<DBGroup>> Group::getGroups()
{
    dbConnection->assertConnectionIsReliable();

    QString request = "SELECT id, name FROM groups;";

    QVector<std::shared_ptr<DBGroup>> groups;

    for (auto &[id, name] : dbConnection->getTransaction()->query<int, std::string>(request.toStdString()))
        groups.append(std::make_shared<DBGroup>(id, QString::fromStdString(name)));

    return groups;
}

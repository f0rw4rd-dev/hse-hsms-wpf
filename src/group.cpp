#include "group.h"
#include "dbconnection.h"

#include <QList>

Group::Group()
{

}

QVector<QSharedPointer<DBGroup>> Group::getGroups()
{
    dbConnection->assertConnectionIsReliable();

    QString request = "SELECT id, name FROM groups;";

    QVector<QSharedPointer<DBGroup>> groups;

    for (auto &[id, name] : dbConnection->getTransaction()->query<int, std::string>(request.toStdString()))
        groups.append(QSharedPointer<DBGroup>(new DBGroup(id, QString::fromStdString(name))));

    return groups;
}

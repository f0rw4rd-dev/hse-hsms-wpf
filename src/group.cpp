#include "group.h"
#include "dbconnection.h"

#include <QList>

QVector<QSharedPointer<Group>> Group::getGroups()
{
    dbConnection->assertConnectionIsReliable();

    QString request = "SELECT id, name FROM groups;";

    QVector<QSharedPointer<Group>> groups;

    for (auto &[id, name] : dbConnection->getTransaction()->query<int, std::string>(request.toStdString()))
        groups.append(QSharedPointer<Group>(new Group(id, QString::fromStdString(name))));

    return groups;
}

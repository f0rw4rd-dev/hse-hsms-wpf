#ifndef GROUP_H
#define GROUP_H

#include <QString>
#include <QSharedPointer>
#include <pqxx/pqxx>

struct DBGroup
{
    DBGroup() {};
    DBGroup(int id, QString name) : id(id), name(name) {};

    int id;
    QString name;
};

class Group
{
public:
    Group();

    static QVector<QSharedPointer<DBGroup>> getGroups();
};

#endif // GROUP_H

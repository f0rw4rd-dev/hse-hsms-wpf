#ifndef GROUP_H
#define GROUP_H

#include <QString>
#include <QSharedPointer>
#include <pqxx/pqxx>

class Group
{
public:
    Group() {};
    Group(int id, QString name) : id(id), name(name) {};

    static QVector<QSharedPointer<Group>> getGroups();

public:
    int id;
    QString name;
};

#endif // GROUP_H

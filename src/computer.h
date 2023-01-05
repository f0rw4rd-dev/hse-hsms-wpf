#ifndef COMPUTER_H
#define COMPUTER_H

#include "component.h"

#include <QVector>
#include <QSharedPointer>
#include <string>

class Computer
{
public:
    Computer() {};
    Computer(int id) : id(id) {};

    static QVector<QSharedPointer<Computer>> getComputers();

public:
    int id;

    QSharedPointer<Component> cpu;
    QSharedPointer<Component> motherboard;
    QSharedPointer<Component> videocard;
    QSharedPointer<Component> ram;
    QSharedPointer<Component> chassis;
    QSharedPointer<Component> psu; // power supply unit
    QSharedPointer<Component> hdd; // can be nullptr
    QSharedPointer<Component> ssd; // can be nullptr
    QSharedPointer<Component> ssdM2; // can be nullptr
    QSharedPointer<Component> fan; // can be nullptr
    QSharedPointer<Component> wcs; // can be nullptr
    QSharedPointer<Component> cooler;
};

#endif // COMPUTER_H

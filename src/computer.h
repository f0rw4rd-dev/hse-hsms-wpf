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

    QScopedPointer<Component> cpu;
    QScopedPointer<Component> motherboard;
    QScopedPointer<Component> videocard;
    QScopedPointer<Component> ram;
    QScopedPointer<Component> chassis;
    QScopedPointer<Component> psu; // power supply unit
    QScopedPointer<Component> hdd; // can be nullptr
    QScopedPointer<Component> ssd; // can be nullptr
    QScopedPointer<Component> ssdM2; // can be nullptr
    QScopedPointer<Component> fan; // can be nullptr
    QScopedPointer<Component> wcs; // can be nullptr
    QScopedPointer<Component> cooler;
};

#endif // COMPUTER_H

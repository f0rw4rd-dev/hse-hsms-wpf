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
    Computer(int cpuId, int motherboardId, int videocardId, int ramId, int ramAmount, int chassisId, int psuId, int hddId, int hddAmount, int ssdId, int ssdAmount, int ssdM2Id, int ssdM2Amount, int fanId, int fanAmount, int wcsId, int coolerId);

    static QVector<QSharedPointer<Computer>> getComputers();
    static QSharedPointer<Computer> getComputer(int id);
    static void addComputer(Computer &computer);
    static void setComputer(Computer &computer);
    static void deleteComputer(int id);

    static bool doesComputerExist(int id);

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

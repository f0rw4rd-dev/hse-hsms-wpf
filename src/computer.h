#ifndef COMPUTER_H
#define COMPUTER_H

#include "component.h"

#include <QVector>
#include <string>

struct DBComputer
{
    DBComputer() {};
    DBComputer(int id, int cpuId, int motherboardId, int videocardId, int ramId, int ramAmount, int caseId, int powersupplyId, int hddId, int hddAmount,
               int ssdId, int ssdAmount, int ssdMTId, int ssdMTAmount, int fanId, int fanAmount, int wcsId, int coolerId)
        : id(id), cpuId(cpuId), motherboardId(motherboardId),
        videocardId(videocardId), ramId(ramId), ramAmount(ramAmount), caseId(caseId), powersupplyId(powersupplyId), hddId(hddId), hddAmount(hddAmount), ssdId(ssdId),
        ssdAmount(ssdAmount), ssdMTId(ssdMTId), ssdMTAmount(ssdMTAmount), fanId(fanId), fanAmount(fanAmount), wcsId(wcsId), coolerId(coolerId)
    {
        const std::string missing = "Отсутствует";

        cpuName = Component::getComponent(cpuId)->name;
        motherboardName = Component::getComponent(motherboardId)->name;
        videocardName = Component::getComponent(videocardId)->name;
        ramName = Component::getComponent(ramId)->name;
        caseName = Component::getComponent(caseId)->name;
        powersupplyName = Component::getComponent(powersupplyId)->name;

        hddName = (hddId != 0) ? Component::getComponent(hddId)->name : missing;
        ssdName = (hddId != 0) ? Component::getComponent(ssdId)->name : missing;
        ssdMTName = (hddId != 0) ? Component::getComponent(ssdMTId)->name : missing;
        wcsName = (hddId != 0) ? Component::getComponent(wcsId)->name : missing;

        fanName = Component::getComponent(fanId)->name;
        coolerName = Component::getComponent(coolerId)->name;
    }

    int id;
    int cpuId;
    std::string cpuName;

    int motherboardId;
    std::string motherboardName;

    int videocardId;
    std::string videocardName;

    int ramId;
    int ramAmount;
    std::string ramName;

    int caseId;
    std::string caseName;

    int powersupplyId;
    std::string powersupplyName;

    int hddId;
    int hddAmount;
    std::string hddName;

    int ssdId;
    int ssdAmount;
    std::string ssdName;

    int ssdMTId;
    int ssdMTAmount;
    std::string ssdMTName;

    int fanId;
    int fanAmount;
    std::string fanName;

    int wcsId;
    std::string wcsName;

    int coolerId;
    std::string coolerName;
};

class Computer
{
public:
    Computer();

    static QVector<std::shared_ptr<DBComputer>> getComputers();
};

#endif // COMPUTER_H

#ifndef COMPUTER_H
#define COMPUTER_H

#include <string>

struct DBComputer
{
    DBComputer() {};
//    DBComputer(int id, int64_t registrationDate, int64_t lastVisitDate, int groupId, std::string groupName)
//        : id(id), registrationDate(registrationDate), lastVisitDate(lastVisitDate), groupId(groupId), groupName(groupName) {};

    int id;
    int cpuId;
    std::string cpuName;

    int motherboardId;

    int videocardId;

    int ramId;
    int ramAmount;

    int caseId;

    int powersupplyId;

    int hddId;
    int hddAmount;

    int ssdId;
    int ssdAmount;

    int ssdMTId;
    int ssdMTAmount;

    int fanId;
    int fanAmount;

    int wcsId;

    int coolerId;
};

class Computer
{
public:
    Computer();

    //static QVector<std::shared_ptr<DBComputer>> getComputers();
};

#endif // COMPUTER_H

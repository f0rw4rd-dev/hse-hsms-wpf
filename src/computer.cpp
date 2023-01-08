#include "computer.h"
#include "dbconnection.h"

Computer::Computer(int cpuId, int motherboardId, int videocardId, int ramId, int ramAmount, int chassisId, int psuId, int hddId, int hddAmount, int ssdId, int ssdAmount, int ssdM2Id, int ssdM2Amount, int fanId, int fanAmount, int wcsId, int coolerId)
{
    cpu.reset(new Component(cpuId));
    motherboard.reset(new Component(motherboardId));

    if (videocardId >= 0)
        videocard.reset(new Component(videocardId));

    ram.reset(new Component(ramId, ramAmount));
    chassis.reset(new Component(chassisId));
    psu.reset(new Component(psuId));

    if (hddId >= 0)
        hdd.reset(new Component(hddId, hddAmount));

    if (ssdId >= 0)
        ssd.reset(new Component(ssdId, ssdAmount));

    if (ssdM2Id >= 0)
        ssdM2.reset(new Component(ssdM2Id, ssdM2Amount));

    if (fanId >= 0)
        fan.reset(new Component(fanId, fanAmount));

    if (wcsId >= 0)
        wcs.reset(new Component(wcsId));

    if (coolerId >= 0)
        cooler.reset(new Component(coolerId));
}

QVector<QSharedPointer<Computer>> Computer::getComputers()
{
    dbConnection->assertConnectionIsReliable();

    QString request = "SELECT * FROM computers";

    QVector<QSharedPointer<Computer>> computers;

    pqxx::result result = dbConnection->getTransaction()->exec(request.toStdString());

    for (const pqxx::row &row : result) {
        QSharedPointer<Computer> computer(new Computer(row["id"].as<int>()));

        computer->cpu = Component::getComponent(row["component_cpu_id"].as<int>());
        computer->motherboard = Component::getComponent(row["component_motherboard_id"].as<int>());
        computer->videocard = Component::getComponent(row["component_videocard_id"].as<int>());
        computer->chassis = Component::getComponent(row["component_case_id"].as<int>());
        computer->psu = Component::getComponent(row["component_powersupply_id"].as<int>());
        computer->cooler = Component::getComponent(row["component_cooler_id"].as<int>());

        computer->ram = Component::getComponent(row["component_ram_id"].as<int>());
        computer->ram->amount = row["component_ram_amount"].as<int>();

        if (int hddId = (row["component_hdd_id"].is_null()) ? 0 : row["component_hdd_id"].as<int>(); hddId != 0) {
            computer->hdd = Component::getComponent(hddId);
            computer->hdd->amount = row["component_hdd_amount"].as<int>();
        } else {
            computer->hdd.reset();
        }

        if (int ssdId = (row["component_ssd_id"].is_null()) ? 0 : row["component_ssd_id"].as<int>(); ssdId != 0) {
            computer->ssd = Component::getComponent(ssdId);
            computer->ssd->amount = row["component_ssd_amount"].as<int>();
        } else {
            computer->ssd.reset();
        }

        if (int ssdM2Id = (row["component_ssdm_id"].is_null()) ? 0 : row["component_ssdm_id"].as<int>(); ssdM2Id != 0) {
            computer->ssdM2 = Component::getComponent(ssdM2Id);
            computer->ssdM2->amount = row["component_ssdm_amount"].as<int>();
        } else {
            computer->ssdM2.reset();
        }

        if (int fanId = (row["component_fan_id"].is_null()) ? 0 : row["component_fan_id"].as<int>(); fanId != 0) {
            computer->fan = Component::getComponent(fanId);
            computer->fan->amount = row["component_fan_amount"].as<int>();
        } else {
            computer->fan.reset();
        }

        if (int wcsId = (row["component_wcs_id"].is_null()) ? 0 : row["component_wcs_id"].as<int>(); wcsId != 0)
            computer->wcs = Component::getComponent(wcsId);
        else
            computer->wcs.reset();

        computers.append(computer);
    }

    return computers;
}

QSharedPointer<Computer> Computer::getComputer(int id)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("SELECT * FROM computers WHERE id = '%1';").arg(QString::number(id));

    pqxx::result component = dbConnection->getTransaction()->exec(request.toStdString());

    if (component.empty())
        return QSharedPointer<Computer>();

    pqxx::row row = component[0];

    auto getComponentId = [](pqxx::field field) { return (field.is_null()) ? -1 : field.as<int>(); };
    auto getComponentAmount = [](pqxx::field field) { return (field.is_null()) ? 0 : field.as<int>(); };

    return QSharedPointer<Computer>(new Computer(
                getComponentId(row["component_cpu_id"]),
                getComponentId(row["component_motherboard_id"]),
                getComponentId(row["component_videocard_id"]),
                getComponentId(row["component_ram_id"]),
                getComponentAmount(row["component_ram_amount"]),
                getComponentId(row["component_case_id"]),
                getComponentId(row["component_powersupply_id"]),
                getComponentId(row["component_hdd_id"]),
                getComponentAmount(row["component_hdd_amount"]),
                getComponentId(row["component_ssd_id"]),
                getComponentAmount(row["component_ssd_amount"]),
                getComponentId(row["component_ssdm_id"]),
                getComponentAmount(row["component_ssdm_amount"]),
                getComponentId(row["component_fan_id"]),
                getComponentAmount(row["component_fan_amount"]),
                getComponentId(row["component_wcs_id"]),
                getComponentId(row["component_cooler_id"])));
}

void Computer::addComputer(Computer &computer)
{
    dbConnection->assertConnectionIsReliable();

    auto getComponentId = [](QSharedPointer<Component> component) { return (component.isNull() || component->id < 1) ? QString("null") : QString::number(component->id); };
    auto getComponentAmount = [](QSharedPointer<Component> component) { return (component.isNull()) ? QString("0") : QString::number(component->amount); };

    QString request = QString("INSERT INTO computers "
                              "(component_cpu_id, component_motherboard_id, component_videocard_id, component_ram_id, component_ram_amount, component_case_id, component_powersupply_id, component_hdd_id, component_hdd_amount, component_ssd_id, component_ssd_amount, component_ssdm_id, component_ssdm_amount, component_fan_id, component_fan_amount, component_wcs_id, component_cooler_id) "
                              "VALUES (%1, %2, %3, %4, %5, %6, %7, %8, %9, %10, %11, %12, %13, %14, %15, %16, %17);")
            .arg(getComponentId(computer.cpu), getComponentId(computer.motherboard), getComponentId(computer.videocard), getComponentId(computer.ram),
                 getComponentAmount(computer.ram), getComponentId(computer.chassis), getComponentId(computer.psu), getComponentId(computer.hdd),
                 getComponentAmount(computer.hdd), getComponentId(computer.ssd), getComponentAmount(computer.ssd), getComponentId(computer.ssdM2),
                 getComponentAmount(computer.ssdM2), getComponentId(computer.fan), getComponentAmount(computer.fan), getComponentId(computer.wcs),
                 getComponentId(computer.cooler));

    dbConnection->getTransaction()->exec(request.toStdString());
    dbConnection->getTransaction()->commit();
}

void Computer::setComputer(Computer &computer)
{
    dbConnection->assertConnectionIsReliable();

    auto getComponentId = [](QSharedPointer<Component> component) { return (component.isNull() || component->id < 1) ? QString("null") : QString::number(component->id); };
    auto getComponentAmount = [](QSharedPointer<Component> component) { return (component.isNull()) ? QString("0") : QString::number(component->amount); };

    QString request = QString("UPDATE computers SET component_cpu_id = %1, component_motherboard_id = %2, component_videocard_id = %3, component_ram_id = %4, component_ram_amount = %5, component_case_id = %6, component_powersupply_id = %7, component_hdd_id = %8, component_hdd_amount = %9, component_ssd_id = %10, component_ssd_amount = %11, component_ssdm_id = %12, component_ssdm_amount = %13, component_fan_id = %14, component_fan_amount = %15, component_wcs_id = %16, component_cooler_id = %17 WHERE id = %18;")
            .arg(getComponentId(computer.cpu), getComponentId(computer.motherboard), getComponentId(computer.videocard), getComponentId(computer.ram),
                 getComponentAmount(computer.ram), getComponentId(computer.chassis), getComponentId(computer.psu), getComponentId(computer.hdd),
                 getComponentAmount(computer.hdd), getComponentId(computer.ssd), getComponentAmount(computer.ssd), getComponentId(computer.ssdM2),
                 getComponentAmount(computer.ssdM2), getComponentId(computer.fan), getComponentAmount(computer.fan), getComponentId(computer.wcs),
                 getComponentId(computer.cooler), QString::number(computer.id));

    dbConnection->getTransaction()->exec(request.toStdString());
    dbConnection->getTransaction()->commit();
}

void Computer::deleteComputer(int id)
{

}

bool Computer::doesComputerExist(int id)
{
    dbConnection->assertConnectionIsReliable();

    QString request = QString("SELECT * FROM computers WHERE id = '%1';").arg(QString::number(id));

    pqxx::result result = dbConnection->getTransaction()->exec(request.toStdString());

    return result.size() != 0;
}

#include "computer.h"
#include "dbconnection.h"

QVector<QSharedPointer<Computer>> Computer::getComputers()
{
    dbConnection->assertConnectionIsReliable();

    QString request = "SELECT * FROM computers";

    QVector<QSharedPointer<Computer>> computers;

    pqxx::result result = dbConnection->getTransaction()->exec(request.toStdString());

    for (const pqxx::row &row : result) {
        QSharedPointer<Computer> computer(new Computer(row["id"].as<int>()));

        //computer->cpu.reset(Component::getComponent(row["component_cpu_id"].as<int>()).get());

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

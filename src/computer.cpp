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

        computer->cpu.reset(Component::getComponent(row["component_cpu_id"].as<int>()).get());
        computer->motherboard.reset(Component::getComponent(row["component_motherboard_id"].as<int>()).get());
        computer->videocard.reset(Component::getComponent(row["component_videocard_id"].as<int>()).get());
        computer->chassis.reset(Component::getComponent(row["component_case_id"].as<int>()).get());
        computer->psu.reset(Component::getComponent(row["component_powersupply_id"].as<int>()).get());
        computer->cooler.reset(Component::getComponent(row["component_cooler_id"].as<int>()).get());

        computer->ram.reset(Component::getComponent(row["component_ram_id"].as<int>()).get());
        computer->ram->amount = row["component_ram_amount"].as<int>();

        if (int hddId = (row["component_hdd_id"].is_null()) ? 0 : row["component_hdd_id"].as<int>(); hddId != 0) {
            computer->hdd.reset(Component::getComponent(hddId).get());
            computer->hdd->amount = row["component_hdd_amount"].as<int>();
        } else {
            computer->hdd.reset();
        }

        if (int ssdId = (row["component_ssd_id"].is_null()) ? 0 : row["component_ssd_id"].as<int>(); ssdId != 0) {
            computer->ssd.reset(Component::getComponent(ssdId).get());
            computer->ssd->amount = row["component_ssd_amount"].as<int>();
        } else {
            computer->ssd.reset();
        }

        if (int ssdM2Id = (row["component_ssdm_id"].is_null()) ? 0 : row["component_ssdm_id"].as<int>(); ssdM2Id != 0) {
            computer->ssdM2.reset(Component::getComponent(ssdM2Id).get());
            computer->ssdM2->amount = row["component_ssdm_amount"].as<int>();
        } else {
            computer->ssdM2.reset();
        }

        if (int fanId = (row["component_fan_id"].is_null()) ? 0 : row["component_fan_id"].as<int>(); fanId != 0) {
            computer->ssdM2.reset(Component::getComponent(fanId).get());
            computer->ssdM2->amount = row["component_fan_amount"].as<int>();
        } else {
            computer->ssdM2.reset();
        }

        if (int wcsId = (row["component_wcs_id"].is_null()) ? 0 : row["component_wcs_id"].as<int>(); wcsId != 0)
            computer->wcs.reset(Component::getComponent(wcsId).get());
        else
            computer->wcs.reset();

        computers.append(computer);
    }

    return computers;
}

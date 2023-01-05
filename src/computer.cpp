#include "computer.h"
#include "dbconnection.h"

#include <QDebug>

Computer::Computer()
{

}

QVector<QSharedPointer<DBComputer>> Computer::getComputers()
{
    dbConnection->assertConnectionIsReliable();

    QString request = "SELECT * FROM computers";

    QVector<QSharedPointer<DBComputer>> computers;

    pqxx::result result = dbConnection->getTransaction()->exec(request.toStdString());

    for (const pqxx::row &row : result) {
        int id = row["id"].as<int>();
        int cpuId = row["component_cpu_id"].as<int>();
        int motherboardId = row["component_motherboard_id"].as<int>();
        int videocardId = row["component_videocard_id"].as<int>();
        int ramId = row["component_ram_id"].as<int>();
        int ramAmount = row["component_ram_amount"].as<int>();
        int caseId = row["component_case_id"].as<int>();
        int powersupplyId = row["component_powersupply_id"].as<int>();
        int hddAmount = row["component_hdd_amount"].as<int>();
        int ssdAmount = row["component_ssd_amount"].as<int>();
        int ssdMTAmount = row["component_ssdm_amount"].as<int>();
        int fanId = row["component_fan_id"].as<int>();
        int fanAmount = row["component_fan_amount"].as<int>();
        int coolerId = row["component_cooler_id"].as<int>();

        // can be null
        int hddId = (row["component_hdd_id"].is_null()) ? 0 : row["component_hdd_id"].as<int>();
        int ssdId = (row["component_ssd_id"].is_null()) ? 0 : row["component_ssd_id"].as<int>();
        int ssdMTId = (row["component_ssdm_id"].is_null()) ? 0 : row["component_ssdm_id"].as<int>();
        int wcsId = (row["component_wcs_id"].is_null()) ? 0 : row["component_wcs_id"].as<int>();


        computers.append(QSharedPointer<DBComputer>(new DBComputer(id, cpuId, motherboardId, videocardId, ramId, ramAmount, caseId, powersupplyId, hddId, hddAmount, ssdId, ssdAmount, ssdMTId, ssdMTAmount, fanId, fanAmount, wcsId, coolerId)));
    }

    return computers;
}

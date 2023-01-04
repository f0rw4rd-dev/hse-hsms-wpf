#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include "component.h"
#include "addcomponentdialog.h"
#include "setcomponentdialog.h"
#include "deletecomponentdialog.h"
#include "user.h"
#include "adduserdialog.h"
#include "setuserdialog.h"
#include "deleteuserdialog.h"
#include "warehouse.h"
#include "addwarehousedialog.h"
#include "setwarehousedialog.h"
#include "deletewarehousedialog.h"
#include "computer.h"
#include "characteristic.h"

#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Adjust MainWindow
    setWindowTitle("HSMS");
    setFixedSize(1000, 600);

    // Init pointers to UI elements
    _tableComponents = findChild<QTableWidget*>("tableComponents");
    _buttonLoadComponents = findChild<QPushButton*>("buttonLoadComponents");
    _buttonAddComponent = findChild<QPushButton*>("buttonAddComponent");
    _buttonSetComponent = findChild<QPushButton*>("buttonSetComponent");
    _buttonDeleteComponent = findChild<QPushButton*>("buttonDeleteComponent");

    _tableUsers = findChild<QTableWidget*>("tableUsers");
    _buttonLoadUsers = findChild<QPushButton*>("buttonLoadUsers");
    _buttonAddUser = findChild<QPushButton*>("buttonAddUser");
    _buttonSetUser = findChild<QPushButton*>("buttonSetUser");
    _buttonDeleteUser = findChild<QPushButton*>("buttonDeleteUser");

    _tableWarehouses = findChild<QTableWidget*>("tableWarehouses");
    _buttonLoadWarehouses = findChild<QPushButton*>("buttonLoadWarehouses");
    _buttonAddWarehouse = findChild<QPushButton*>("buttonAddWarehouse");
    _buttonSetWarehouse = findChild<QPushButton*>("buttonSetWarehouse");
    _buttonDeleteWarehouse = findChild<QPushButton*>("buttonDeleteWarehouse");

    _tableComputers = findChild<QTableWidget*>("tableComputers");
    _buttonLoadComputers = findChild<QPushButton*>("buttonLoadComputers");

    _tableCharacteristics = findChild<QTableWidget*>("tableCharacteristics");
    _buttonLoadCharacteristics = findChild<QPushButton*>("buttonLoadCharacteristics");

    _tableWarehouseComponents = findChild<QTableWidget*>("tableWarehouseComponents");
    _buttonLoadWarehouseComponents = findChild<QPushButton*>("buttonLoadWarehouseComponents");

    _stackedWidget = findChild<QStackedWidget*>("stackedWidget");

    // Open LoginWindow
    _stackedWidget->addWidget(new LoginWindow(this));
    _stackedWidget->setCurrentIndex(1);

    // Connections
    connect(_buttonLoadComponents, &QPushButton::clicked, this, &MainWindow::loadComponents);
    connect(_buttonAddComponent, &QPushButton::clicked, this, &MainWindow::addComponent);
    connect(_buttonSetComponent, &QPushButton::clicked, this, &MainWindow::setComponent);
    connect(_buttonDeleteComponent, &QPushButton::clicked, this, &MainWindow::deleteComponent);

    connect(_buttonLoadUsers, &QPushButton::clicked, this, &MainWindow::loadUsers);
    connect(_buttonAddUser, &QPushButton::clicked, this, &MainWindow::addUser);
    connect(_buttonSetUser, &QPushButton::clicked, this, &MainWindow::setUser);
    connect(_buttonDeleteUser, &QPushButton::clicked, this, &MainWindow::deleteUser);

    connect(_buttonLoadWarehouses, &QPushButton::clicked, this, &MainWindow::loadWarehouses);
    connect(_buttonAddWarehouse, &QPushButton::clicked, this, &MainWindow::addWarehouse);
    connect(_buttonSetWarehouse, &QPushButton::clicked, this, &MainWindow::setWarehouse);
    connect(_buttonDeleteWarehouse, &QPushButton::clicked, this, &MainWindow::deleteWarehouse);

    connect(_buttonLoadComputers, &QPushButton::clicked, this, &MainWindow::loadComputers);

    connect(_buttonLoadCharacteristics, &QPushButton::clicked, this, &MainWindow::loadCharacteristics);

    connect(_buttonLoadWarehouseComponents, &QPushButton::clicked, this, &MainWindow::loadWarehouseComponents);

    // Fill tables with data
    loadComponents();
    loadUsers();
    loadWarehouses();
    loadComputers();
    loadCharacteristics();
    loadWarehouseComponents();

    // Remove the first column in tables
    auto setupTable = [](QTableWidget *table) {
        table->verticalHeader()->setVisible(false);
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    };

    setupTable(_tableComponents);
    setupTable(_tableUsers);
    setupTable(_tableWarehouses);

    parentWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadComponents()
{
    _tableComponents->setRowCount(0);

    for (QSharedPointer<DBComponent> &dbComponent : Component::getComponents()) {
        int row = _tableComponents->rowCount();

        _tableComponents->insertRow(row);

        _tableComponents->setItem(row, 0, new QTableWidgetItem(QString::number(dbComponent->id)));
        _tableComponents->setItem(row, 1, new QTableWidgetItem(dbComponent->componentType->name));
        _tableComponents->setItem(row, 2, new QTableWidgetItem(dbComponent->name));
        _tableComponents->setItem(row, 3, new QTableWidgetItem(QString::number(dbComponent->warranty)));
        _tableComponents->setItem(row, 4, new QTableWidgetItem(QString::number(dbComponent->price)));
    }
}

void MainWindow::addComponent()
{
    AddComponentDialog *addComponentDialog = new AddComponentDialog(this);

    //QScopedPointer<AddComponentDialog, QScopedPointerDeleteLater> addComponentDialog(new AddComponentDialog(this));

    //AddComponentDialog addComponentDialog(this);
    addComponentDialog->show();
}

void MainWindow::setComponent()
{
    SetComponentDialog *setComponentDialog = new SetComponentDialog(this);
    setComponentDialog->show();
}

void MainWindow::deleteComponent()
{
    DeleteComponentDialog *deleteComponentDialog = new DeleteComponentDialog(this);
    deleteComponentDialog->show();
}

void MainWindow::loadUsers()
{
    _tableUsers->setRowCount(0);

    for (QSharedPointer<DBUser> &dbUser : User::getUsers()) {
        int row = _tableUsers->rowCount();

        _tableUsers->insertRow(row);

        _tableUsers->setItem(row, 0, new QTableWidgetItem(QString::number(dbUser->id)));
        _tableUsers->setItem(row, 1, new QTableWidgetItem(QDateTime::fromSecsSinceEpoch(dbUser->registrationDate).toString("dd/MM/yyyy hh:mm:ss")));
        _tableUsers->setItem(row, 2, new QTableWidgetItem(QDateTime::fromSecsSinceEpoch(dbUser->lastVisitDate).toString("dd/MM/yyyy hh:mm:ss")));
        _tableUsers->setItem(row, 3, new QTableWidgetItem(dbUser->group->name));
    }
}

void MainWindow::addUser()
{
    AddUserDialog *addUserDialog = new AddUserDialog(this);
    addUserDialog->show();
}

void MainWindow::setUser()
{
    SetUserDialog *setUserDialog = new SetUserDialog(this);
    setUserDialog->show();
}

void MainWindow::deleteUser()
{
    DeleteUserDialog *deleteUserDialog = new DeleteUserDialog(this);
    deleteUserDialog->show();
}

void MainWindow::loadWarehouses()
{
    _tableWarehouses->setRowCount(0);

    for (QSharedPointer<DBWarehouse> &dbWarehouse : Warehouse::getWarehouses()) {
        int row = _tableWarehouses->rowCount();

        _tableWarehouses->insertRow(row);

        _tableWarehouses->setItem(row, 0, new QTableWidgetItem(QString::number(dbWarehouse->id)));
        _tableWarehouses->setItem(row, 1, new QTableWidgetItem(dbWarehouse->city));
        _tableWarehouses->setItem(row, 2, new QTableWidgetItem(dbWarehouse->street));
        _tableWarehouses->setItem(row, 3, new QTableWidgetItem(QString::number(dbWarehouse->house)));
        _tableWarehouses->setItem(row, 4, new QTableWidgetItem(QString::number(dbWarehouse->zip)));
    }
}

void MainWindow::addWarehouse()
{
    AddWarehouseDialog *addWarehouseDialog = new AddWarehouseDialog(this);
    addWarehouseDialog->show();
}

void MainWindow::setWarehouse()
{
    SetWarehouseDialog *setWarehouseDialog = new SetWarehouseDialog(this);
    setWarehouseDialog->show();
}

void MainWindow::deleteWarehouse()
{
    DeleteWarehouseDialog *deleteWarehouseDialog = new DeleteWarehouseDialog(this);
    deleteWarehouseDialog->show();
}

void MainWindow::loadComputers()
{
    _tableComputers->setRowCount(0);

    for (QSharedPointer<DBComputer> &dbComputers : Computer::getComputers()) {
        int row = _tableComputers->rowCount();

        _tableComputers->insertRow(row);

        _tableComputers->setItem(row, 0, new QTableWidgetItem(QString::number(dbComputers->id)));

        QString componentFormat("#%1 %2");
        QString componentWithAmountFormat("#%1 %2 (%3)");

        _tableComputers->setItem(row, 1, new QTableWidgetItem(componentFormat.arg(QString::number(dbComputers->cpuId), dbComputers->cpuName)));
        _tableComputers->setItem(row, 2, new QTableWidgetItem(componentFormat.arg(QString::number(dbComputers->motherboardId), dbComputers->motherboardName)));
        _tableComputers->setItem(row, 3, new QTableWidgetItem(componentFormat.arg(QString::number(dbComputers->videocardId), dbComputers->videocardName)));
        _tableComputers->setItem(row, 4, new QTableWidgetItem(componentWithAmountFormat.arg(QString::number(dbComputers->ramId), dbComputers->ramName, QString::number(dbComputers->ramAmount))));
        _tableComputers->setItem(row, 5, new QTableWidgetItem(componentFormat.arg(QString::number(dbComputers->caseId), dbComputers->caseName)));
        _tableComputers->setItem(row, 6, new QTableWidgetItem(componentFormat.arg(QString::number(dbComputers->powersupplyId), dbComputers->powersupplyName)));

        if (dbComputers->hddId == 0)
            _tableComputers->setItem(row, 7, new QTableWidgetItem(dbComputers->hddName));
        else
            _tableComputers->setItem(row, 7, new QTableWidgetItem(componentWithAmountFormat.arg(QString::number(dbComputers->hddId), dbComputers->hddName, QString::number(dbComputers->hddAmount))));

        if (dbComputers->ssdId == 0)
            _tableComputers->setItem(row, 8, new QTableWidgetItem(dbComputers->ssdName));
        else
            _tableComputers->setItem(row, 8, new QTableWidgetItem(componentWithAmountFormat.arg(QString::number(dbComputers->ssdId), dbComputers->ssdName, QString::number(dbComputers->ssdAmount))));

        if (dbComputers->ssdMTId == 0)
            _tableComputers->setItem(row, 9, new QTableWidgetItem(dbComputers->ssdMTName));
        else
            _tableComputers->setItem(row, 9, new QTableWidgetItem(componentWithAmountFormat.arg(QString::number(dbComputers->ssdMTId), dbComputers->ssdMTName, QString::number(dbComputers->ssdMTAmount))));

        _tableComputers->setItem(row, 10, new QTableWidgetItem(componentWithAmountFormat.arg(QString::number(dbComputers->fanId), dbComputers->fanName, QString::number(dbComputers->fanAmount))));

        if (dbComputers->wcsId == 0)
            _tableComputers->setItem(row, 11, new QTableWidgetItem(dbComputers->wcsName));
        else
            _tableComputers->setItem(row, 11, new QTableWidgetItem(componentFormat.arg(QString::number(dbComputers->wcsId), dbComputers->wcsName)));

        _tableComputers->setItem(row, 12, new QTableWidgetItem(componentFormat.arg(QString::number(dbComputers->coolerId), dbComputers->coolerName)));
    }
}

void MainWindow::addComputer()
{

}

void MainWindow::loadCharacteristics()
{
    _tableCharacteristics->setRowCount(0);

    for (QSharedPointer<DBCharacteristic> &dbCharacteristic : Characteristic::getCharacteristics()) {
        int row = _tableCharacteristics->rowCount();

        _tableCharacteristics->insertRow(row);

        _tableCharacteristics->setItem(row, 0, new QTableWidgetItem(QString::number(dbCharacteristic->id)));
        _tableCharacteristics->setItem(row, 1, new QTableWidgetItem(dbCharacteristic->componentName));
        _tableCharacteristics->setItem(row, 2, new QTableWidgetItem(dbCharacteristic->characteristicTypeName));
        _tableCharacteristics->setItem(row, 3, new QTableWidgetItem(dbCharacteristic->value));
    }
}

void MainWindow::loadWarehouseComponents()
{
    _tableWarehouseComponents->setRowCount(0);

    for (QSharedPointer<DBWarehouseComponent> &dbComponentInWarehouse : Warehouse::getWarehouseComponents()) {
        int row = _tableWarehouseComponents->rowCount();

        _tableWarehouseComponents->insertRow(row);

        _tableWarehouseComponents->setItem(row, 0, new QTableWidgetItem(dbComponentInWarehouse->component->name));
        _tableWarehouseComponents->setItem(row, 1, new QTableWidgetItem(dbComponentInWarehouse->warehouse->city));
        _tableWarehouseComponents->setItem(row, 2, new QTableWidgetItem(QString::number(dbComponentInWarehouse->amount)));
    }
}

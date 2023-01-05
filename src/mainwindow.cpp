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
#include "warehousecomponent.h"
#include "addwarehousecomponentdialog.h"
#include "setwarehousecomponentdialog.h"
#include "deletewarehousecomponentdialog.h"
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
    _buttonAddWarehouseComponent = findChild<QPushButton*>("buttonAddWarehouseComponent");
    _buttonSetWarehouseComponent = findChild<QPushButton*>("buttonSetWarehouseComponent");
    _buttonDeleteWarehouseComponent = findChild<QPushButton*>("buttonDeleteWarehouseComponent");

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
    connect(_buttonAddWarehouseComponent, &QPushButton::clicked, this, &MainWindow::addWarehouseComponent);
    connect(_buttonSetWarehouseComponent, &QPushButton::clicked, this, &MainWindow::setWarehouseComponent);
    connect(_buttonDeleteWarehouseComponent, &QPushButton::clicked, this, &MainWindow::deleteWarehouseComponent);

    // Fill tables with data
    loadComponents();
    loadUsers();
    loadWarehouses();
    loadComputers();
    loadCharacteristics();
    loadWarehouseComponents();

    // Remove the first column in tables
    auto setupTable = [](QTableWidget *table, bool stretchLastSection = false) {
        table->verticalHeader()->setVisible(false);

        (stretchLastSection) ? table->horizontalHeader()->setStretchLastSection(true)
                             : table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    };

    setupTable(_tableComponents);
    setupTable(_tableUsers);
    setupTable(_tableWarehouses);
    setupTable(_tableComputers, true);
    setupTable(_tableWarehouseComponents);

    parentWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadComponents()
{
    _tableComponents->setRowCount(0);

    for (QSharedPointer<Component> &dbComponent : Component::getComponents()) {
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

    for (QSharedPointer<User> &user : User::getUsers()) {
        int row = _tableUsers->rowCount();

        _tableUsers->insertRow(row);

        _tableUsers->setItem(row, 0, new QTableWidgetItem(QString::number(user->id)));
        _tableUsers->setItem(row, 1, new QTableWidgetItem(QDateTime::fromSecsSinceEpoch(user->registrationDate).toString("dd/MM/yyyy hh:mm:ss")));
        _tableUsers->setItem(row, 2, new QTableWidgetItem(QDateTime::fromSecsSinceEpoch(user->lastVisitDate).toString("dd/MM/yyyy hh:mm:ss")));
        _tableUsers->setItem(row, 3, new QTableWidgetItem(user->group->name));
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

    for (QSharedPointer<Warehouse> &warehouse : Warehouse::getWarehouses()) {
        int row = _tableWarehouses->rowCount();

        _tableWarehouses->insertRow(row);

        _tableWarehouses->setItem(row, 0, new QTableWidgetItem(QString::number(warehouse->id)));
        _tableWarehouses->setItem(row, 1, new QTableWidgetItem(warehouse->city));
        _tableWarehouses->setItem(row, 2, new QTableWidgetItem(warehouse->street));
        _tableWarehouses->setItem(row, 3, new QTableWidgetItem(QString::number(warehouse->house)));
        _tableWarehouses->setItem(row, 4, new QTableWidgetItem(QString::number(warehouse->zip)));
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

    for (QSharedPointer<Computer> &computers : Computer::getComputers()) {
        int row = 0;

        for (int i = row; i < row + 12; i++)
            _tableComputers->insertRow(i);

        _tableComputers->setItem(row, 0, new QTableWidgetItem(QString::number(computers->id)));

        QString componentFormat("%1 - [%2] %3");
        QString componentWithAmountFormat("%1 - [%2] %3 - x%4");
        QString componentMissingFormat("%1 - Отсутствует");

        _tableComputers->setItem(row + 1, 1, new QTableWidgetItem(componentFormat.arg("Процессор", QString::number(computers->cpu->id), computers->cpu->name)));
        _tableComputers->setItem(row + 2, 1, new QTableWidgetItem(componentFormat.arg(QString::number(computers->motherboard->id), computers->motherboard->name)));
        _tableComputers->setItem(row + 3, 1, new QTableWidgetItem(componentFormat.arg(QString::number(computers->videocard->id), computers->videocard->name)));
        _tableComputers->setItem(row + 4, 1, new QTableWidgetItem(componentWithAmountFormat.arg(QString::number(computers->ram->id), computers->ram->name, QString::number(computers->ram->amount))));
        _tableComputers->setItem(row + 5, 1, new QTableWidgetItem(componentFormat.arg(QString::number(computers->chassis->id), computers->chassis->name)));
        _tableComputers->setItem(row + 6, 1, new QTableWidgetItem(componentFormat.arg(QString::number(computers->psu->id), computers->psu->name)));

        if (computers->hdd.isNull())
            _tableComputers->setItem(row + 7, 1, new QTableWidgetItem(componentMissingFormat.arg("HDD")));
        else
            _tableComputers->setItem(row + 7, 1, new QTableWidgetItem(componentWithAmountFormat.arg(QString::number(computers->hdd->id), computers->hdd->name, QString::number(computers->hdd->amount))));

        if (computers->ssd.isNull())
            _tableComputers->setItem(row + 8, 1, new QTableWidgetItem(componentMissingFormat.arg("SSD")));
        else
            _tableComputers->setItem(row + 8, 1, new QTableWidgetItem(componentWithAmountFormat.arg(QString::number(computers->ssd->id), computers->ssd->name, QString::number(computers->ssd->amount))));

        if (computers->ssdM2.isNull())
            _tableComputers->setItem(row + 9, 1, new QTableWidgetItem(componentMissingFormat.arg("SSD M.2")));
        else
            _tableComputers->setItem(row + 9, 1, new QTableWidgetItem(componentWithAmountFormat.arg(QString::number(computers->ssdM2->id), computers->ssdM2->name, QString::number(computers->ssdM2->amount))));

        _tableComputers->setItem(row + 10, 1, new QTableWidgetItem(componentWithAmountFormat.arg(QString::number(computers->fan->id), computers->fan->name, QString::number(computers->fan->amount))));

        if (computers->wcs.isNull())
            _tableComputers->setItem(row + 11, 1, new QTableWidgetItem(componentMissingFormat.arg("СЖО")));
        else
            _tableComputers->setItem(row + 11, 1, new QTableWidgetItem(componentFormat.arg(QString::number(computers->wcs->id), computers->wcs->name)));

        _tableComputers->setItem(row + 12, 1, new QTableWidgetItem(componentFormat.arg(QString::number(computers->cooler->id), computers->cooler->name)));

        row += 12;
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

    for (QSharedPointer<WarehouseComponent> &warehouseComponent : WarehouseComponent::getWarehouseComponents()) {
        int row = _tableWarehouseComponents->rowCount();

        _tableWarehouseComponents->insertRow(row);

        _tableWarehouseComponents->setItem(row, 0, new QTableWidgetItem(QString("[%1] %2").arg(QString::number(warehouseComponent->component->id), warehouseComponent->component->name)));
        _tableWarehouseComponents->setItem(row, 1, new QTableWidgetItem(QString("[%1] %2").arg(QString::number(warehouseComponent->warehouse->id), Warehouse::getAddress(*warehouseComponent->warehouse))));
        _tableWarehouseComponents->setItem(row, 2, new QTableWidgetItem(QString::number(warehouseComponent->amount)));
    }
}

void MainWindow::addWarehouseComponent()
{
    AddWarehouseComponentDialog *addWarehouseComponentDialog = new AddWarehouseComponentDialog(this);
    addWarehouseComponentDialog->show();
}

void MainWindow::setWarehouseComponent()
{
    SetWarehouseComponentDialog *setWarehouseComponentDialog = new SetWarehouseComponentDialog(this);
    setWarehouseComponentDialog->show();
}

void MainWindow::deleteWarehouseComponent()
{
    DeleteWarehouseComponentDialog *deleteWarehouseComponentDialog = new DeleteWarehouseComponentDialog(this);
    deleteWarehouseComponentDialog->show();
}

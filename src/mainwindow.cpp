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
#include "addcomputerdialog.h"
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
    _buttonAddComputer = findChild<QPushButton*>("buttonAddComputer");
    _buttonSetComputer = findChild<QPushButton*>("buttonSetComputer");
    _buttonDeleteComputer = findChild<QPushButton*>("buttonDeleteComputer");

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
    connect(_buttonAddComputer, &QPushButton::clicked, this, &MainWindow::addComputer);
    //connect(_buttonSetComputer, &QPushButton::clicked, this, &MainWindow::setComputer);
    //connect(_buttonDeleteComputer, &QPushButton::clicked, this, &MainWindow::deleteComputer);

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
    auto setupTable = [](QTableWidget *table) {
        table->verticalHeader()->setVisible(false);
        table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        table->horizontalHeader()->setSectionsMovable(true);
    };

    setupTable(_tableComponents);
    setupTable(_tableUsers);
    setupTable(_tableWarehouses);
    setupTable(_tableComputers);
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

    QVector<QString> componentTypes = {"Процессор", "Материнская плата", "Видеокарта", "Оперативная память", "Корпус", "Блок питания", "HDD", "SSD", "SSD M.2", "Вентилятор", "Система водяного охлаждения", "Кулер"};

    for (QSharedPointer<Computer> &computer : Computer::getComputers()) {
        int row = 0;

        for (int i = row; i < row + 12; i++) {
            _tableComputers->insertRow(row + i);
            _tableComputers->setItem(row + i, 0, new QTableWidgetItem(QString::number(computer->id)));
            _tableComputers->setItem(row + i, 1, new QTableWidgetItem(componentTypes[i]));
        }

        QString componentFormat("[%1] %2");
        QString componentMissingFormat("Отсутствует");

        _tableComputers->setItem(row, 2, new QTableWidgetItem(componentFormat.arg(QString::number(computer->cpu->id), computer->cpu->name)));
        _tableComputers->setItem(row + 1, 2, new QTableWidgetItem(componentFormat.arg(QString::number(computer->motherboard->id), computer->motherboard->name)));
        _tableComputers->setItem(row + 2, 2, new QTableWidgetItem(componentFormat.arg(QString::number(computer->videocard->id), computer->videocard->name)));
        _tableComputers->setItem(row + 3, 2, new QTableWidgetItem(componentFormat.arg(QString::number(computer->ram->id), computer->ram->name)));
        _tableComputers->setItem(row + 3, 3, new QTableWidgetItem(QString::number(computer->ram->amount)));
        _tableComputers->setItem(row + 4, 2, new QTableWidgetItem(componentFormat.arg(QString::number(computer->chassis->id), computer->chassis->name)));
        _tableComputers->setItem(row + 5, 2, new QTableWidgetItem(componentFormat.arg(QString::number(computer->psu->id), computer->psu->name)));

        if (computer->hdd.isNull()) {
            _tableComputers->setItem(row + 6, 2, new QTableWidgetItem(componentMissingFormat));
        } else {
            _tableComputers->setItem(row + 6, 2, new QTableWidgetItem(componentFormat.arg(QString::number(computer->hdd->id), computer->hdd->name)));
            _tableComputers->setItem(row + 6, 3, new QTableWidgetItem(QString::number(computer->hdd->amount)));
        }

        if (computer->ssd.isNull()) {
            _tableComputers->setItem(row + 7, 2, new QTableWidgetItem(componentMissingFormat));
        } else {
            _tableComputers->setItem(row + 7, 2, new QTableWidgetItem(componentFormat.arg(QString::number(computer->ssd->id), computer->ssd->name)));
            _tableComputers->setItem(row + 7, 3, new QTableWidgetItem(QString::number(computer->ssd->amount)));
        }

        if (computer->ssdM2.isNull()) {
            _tableComputers->setItem(row + 8, 2, new QTableWidgetItem(componentMissingFormat));
        } else {
            _tableComputers->setItem(row + 8, 2, new QTableWidgetItem(componentFormat.arg(QString::number(computer->ssdM2->id), computer->ssdM2->name)));
            _tableComputers->setItem(row + 8, 3, new QTableWidgetItem(QString::number(computer->ssdM2->amount)));
        }

        _tableComputers->setItem(row + 9, 2, new QTableWidgetItem(componentFormat.arg(QString::number(computer->fan->id), computer->fan->name)));
        _tableComputers->setItem(row + 9, 3, new QTableWidgetItem(QString::number(computer->fan->amount)));

        if (computer->wcs.isNull()) {
            _tableComputers->setItem(row + 10, 2, new QTableWidgetItem(componentMissingFormat));
        } else {
            _tableComputers->setItem(row + 10, 2, new QTableWidgetItem(componentFormat.arg(QString::number(computer->wcs->id), computer->wcs->name)));
        }

        _tableComputers->setItem(row + 11, 2, new QTableWidgetItem(componentFormat.arg(QString::number(computer->cooler->id), computer->cooler->name)));

        _tableComputers->setSpan(row, 0, row + 12, 1);
        row += 12;
    }
}

void MainWindow::addComputer()
{
    AddComputerDialog *addComputerDialog = new AddComputerDialog(this);
    addComputerDialog->show();
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

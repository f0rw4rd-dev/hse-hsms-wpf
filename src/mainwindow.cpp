#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include "component.h"
#include "addcomponentdialog.h"
#include "editcomponentdialog.h"
#include "deletecomponentdialog.h"
#include "user.h"
#include "warehouse.h"
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
    _buttonEditComponent = findChild<QPushButton*>("buttonEditComponent");
    _buttonDeleteComponent = findChild<QPushButton*>("buttonDeleteComponent");

    _tableUsers = findChild<QTableWidget*>("tableUsers");
    _buttonLoadUsers = findChild<QPushButton*>("buttonLoadUsers");

    _tableWarehouses = findChild<QTableWidget*>("tableWarehouses");
    _buttonLoadWarehouses = findChild<QPushButton*>("buttonLoadWarehouses");

    _tableComputers = findChild<QTableWidget*>("tableComputers");
    _buttonLoadComputers = findChild<QPushButton*>("buttonLoadComputers");

    _tableCharacteristics = findChild<QTableWidget*>("tableCharacteristics");
    _buttonLoadCharacteristics = findChild<QPushButton*>("buttonLoadCharacteristics");

    _tableComponentsInWarehouses = findChild<QTableWidget*>("tableComponentsInWarehouses");
    _buttonLoadComponentsInWarehouses = findChild<QPushButton*>("buttonLoadComponentsInWarehouses");

    _stackedWidget = findChild<QStackedWidget*>("stackedWidget");

    // Open LoginWindow
    _stackedWidget->addWidget(new LoginWindow(this));
    _stackedWidget->setCurrentIndex(1);

    // Connections
    connect(_buttonLoadComponents, &QPushButton::clicked, this, &MainWindow::loadComponents);
    connect(_buttonAddComponent, &QPushButton::clicked, this, &MainWindow::addComponent);
    connect(_buttonEditComponent, &QPushButton::clicked, this, &MainWindow::editComponent);
    connect(_buttonDeleteComponent, &QPushButton::clicked, this, &MainWindow::deleteComponent);

    connect(_buttonLoadUsers, &QPushButton::clicked, this, &MainWindow::loadUsers);

    connect(_buttonLoadWarehouses, &QPushButton::clicked, this, &MainWindow::loadWarehouses);

    connect(_buttonLoadComputers, &QPushButton::clicked, this, &MainWindow::loadComputers);

    connect(_buttonLoadCharacteristics, &QPushButton::clicked, this, &MainWindow::loadCharacteristics);

    connect(_buttonLoadComponentsInWarehouses, &QPushButton::clicked, this, &MainWindow::loadComponentsInWarehouses);

    // Fill tables with data
    loadComponents();
    loadUsers();
    loadWarehouses();
    loadComputers();
    loadCharacteristics();
    loadComponentsInWarehouses();

    parentWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadComponents()
{
    _tableComponents->setRowCount(0);

    for (std::shared_ptr<DBComponent> &dbComponent : Component::getComponents()) {
        int row = _tableComponents->rowCount();

        _tableComponents->insertRow(row);

        _tableComponents->setItem(row, 0, new QTableWidgetItem(QString::number(dbComponent->id)));
        _tableComponents->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(dbComponent->typeName)));
        _tableComponents->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(dbComponent->name)));
        _tableComponents->setItem(row, 3, new QTableWidgetItem(QString::number(dbComponent->warranty)));
        _tableComponents->setItem(row, 4, new QTableWidgetItem(QString::number(dbComponent->price)));
    }
}

void MainWindow::addComponent()
{
    AddComponentDialog *addComponentDialog = new AddComponentDialog(this);
    addComponentDialog->show();
}

void MainWindow::editComponent()
{
    EditComponentDialog *editComponentDialog = new EditComponentDialog(this);
    editComponentDialog->show();
}

void MainWindow::deleteComponent()
{
    DeleteComponentDialog *deleteComponentDialog = new DeleteComponentDialog(this);
    deleteComponentDialog->show();
}

void MainWindow::loadUsers()
{
    _tableUsers->setRowCount(0);

    for (std::shared_ptr<DBUser> &dbUser : User::getUsers()) {
        int row = _tableUsers->rowCount();

        _tableUsers->insertRow(row);

        _tableUsers->setItem(row, 0, new QTableWidgetItem(QString::number(dbUser->id)));
        _tableUsers->setItem(row, 1, new QTableWidgetItem(QDateTime::fromSecsSinceEpoch(dbUser->registrationDate).toString("dd/MM/yyyy hh:mm:ss")));
        _tableUsers->setItem(row, 2, new QTableWidgetItem(QDateTime::fromSecsSinceEpoch(dbUser->lastVisitDate).toString("dd/MM/yyyy hh:mm:ss")));
        _tableUsers->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(dbUser->groupName)));
    }
}

void MainWindow::loadWarehouses()
{
    _tableWarehouses->setRowCount(0);

    for (std::shared_ptr<DBWarehouse> &dbWarehouse : Warehouse::getWarehouses()) {
        int row = _tableWarehouses->rowCount();

        _tableWarehouses->insertRow(row);

        _tableWarehouses->setItem(row, 0, new QTableWidgetItem(QString::number(dbWarehouse->id)));
        _tableWarehouses->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(dbWarehouse->address)));
    }
}

void MainWindow::loadComputers()
{
    _tableComputers->setRowCount(0);

    for (std::shared_ptr<DBComputer> &dbComputers : Computer::getComputers()) {
        int row = _tableComputers->rowCount();

        _tableComputers->insertRow(row);

        _tableComputers->setItem(row, 0, new QTableWidgetItem(QString::number(dbComputers->id)));

        QString componentFormat("#%1 %2");
        QString componentWithAmountFormat("#%1 %2 (%3)");

        _tableComputers->setItem(row, 1, new QTableWidgetItem(componentFormat.arg(QString::number(dbComputers->cpuId), QString::fromStdString(dbComputers->cpuName))));
        _tableComputers->setItem(row, 2, new QTableWidgetItem(componentFormat.arg(QString::number(dbComputers->motherboardId), QString::fromStdString(dbComputers->motherboardName))));
        _tableComputers->setItem(row, 3, new QTableWidgetItem(componentFormat.arg(QString::number(dbComputers->videocardId), QString::fromStdString(dbComputers->videocardName))));
        _tableComputers->setItem(row, 4, new QTableWidgetItem(componentWithAmountFormat.arg(QString::number(dbComputers->ramId), QString::fromStdString(dbComputers->ramName), QString::number(dbComputers->ramAmount))));
        _tableComputers->setItem(row, 5, new QTableWidgetItem(componentFormat.arg(QString::number(dbComputers->caseId), QString::fromStdString(dbComputers->caseName))));
        _tableComputers->setItem(row, 6, new QTableWidgetItem(componentFormat.arg(QString::number(dbComputers->powersupplyId), QString::fromStdString(dbComputers->powersupplyName))));

        if (dbComputers->hddId == 0)
            _tableComputers->setItem(row, 7, new QTableWidgetItem(QString::fromStdString(dbComputers->hddName)));
        else
            _tableComputers->setItem(row, 7, new QTableWidgetItem(componentWithAmountFormat.arg(QString::number(dbComputers->hddId), QString::fromStdString(dbComputers->hddName), QString::number(dbComputers->hddAmount))));

        if (dbComputers->ssdId == 0)
            _tableComputers->setItem(row, 8, new QTableWidgetItem(QString::fromStdString(dbComputers->ssdName)));
        else
            _tableComputers->setItem(row, 8, new QTableWidgetItem(componentWithAmountFormat.arg(QString::number(dbComputers->ssdId), QString::fromStdString(dbComputers->ssdName), QString::number(dbComputers->ssdAmount))));

        if (dbComputers->ssdMTId == 0)
            _tableComputers->setItem(row, 9, new QTableWidgetItem(QString::fromStdString(dbComputers->ssdMTName)));
        else
            _tableComputers->setItem(row, 9, new QTableWidgetItem(componentWithAmountFormat.arg(QString::number(dbComputers->ssdMTId), QString::fromStdString(dbComputers->ssdMTName), QString::number(dbComputers->ssdMTAmount))));

        _tableComputers->setItem(row, 10, new QTableWidgetItem(componentWithAmountFormat.arg(QString::number(dbComputers->fanId), QString::fromStdString(dbComputers->fanName), QString::number(dbComputers->fanAmount))));

        if (dbComputers->wcsId == 0)
            _tableComputers->setItem(row, 11, new QTableWidgetItem(QString::fromStdString(dbComputers->wcsName)));
        else
            _tableComputers->setItem(row, 11, new QTableWidgetItem(componentFormat.arg(QString::number(dbComputers->wcsId), QString::fromStdString(dbComputers->wcsName))));

        _tableComputers->setItem(row, 12, new QTableWidgetItem(componentFormat.arg(QString::number(dbComputers->coolerId), QString::fromStdString(dbComputers->coolerName))));
    }
}

void MainWindow::loadCharacteristics()
{
    _tableCharacteristics->setRowCount(0);

    for (std::shared_ptr<DBCharacteristic> &dbCharacteristic : Characteristic::getCharacteristics()) {
        int row = _tableCharacteristics->rowCount();

        _tableCharacteristics->insertRow(row);

        _tableCharacteristics->setItem(row, 0, new QTableWidgetItem(QString::number(dbCharacteristic->id)));
        _tableCharacteristics->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(dbCharacteristic->componentName)));
        _tableCharacteristics->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(dbCharacteristic->characteristicTypeName)));
        _tableCharacteristics->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(dbCharacteristic->value)));
    }
}

void MainWindow::loadComponentsInWarehouses()
{
    _tableComponentsInWarehouses->setRowCount(0);

    for (std::shared_ptr<DBComponentInWarehouse> &dbComponentInWarehouse : Warehouse::getComponentsInWarehouses()) {
        int row = _tableComponentsInWarehouses->rowCount();

        _tableComponentsInWarehouses->insertRow(row);

        _tableComponentsInWarehouses->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(dbComponentInWarehouse->componentName)));
        _tableComponentsInWarehouses->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(dbComponentInWarehouse->address)));
        _tableComponentsInWarehouses->setItem(row, 2, new QTableWidgetItem(QString::number(dbComponentInWarehouse->amount)));
    }
}

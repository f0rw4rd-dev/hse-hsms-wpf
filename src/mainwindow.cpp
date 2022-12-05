#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loginwindow.h"
#include "component.h"
#include "addcomponentdialog.h"
#include "editcomponentdialog.h"
#include "deletecomponentdialog.h"
#include "user.h"
#include "warehouse.h"

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

    _tableWarehouses = findChild<QTableWidget*>("tableWarehouses");

    _stackedWidget = findChild<QStackedWidget*>("stackedWidget");

    // Open LoginWindow
    _stackedWidget->addWidget(new LoginWindow(this));
    _stackedWidget->setCurrentIndex(1);

    // Connections
    connect(_buttonLoadComponents, &QPushButton::clicked, this, &MainWindow::loadComponents);
    connect(_buttonAddComponent, &QPushButton::clicked, this, &MainWindow::addComponent);
    connect(_buttonEditComponent, &QPushButton::clicked, this, &MainWindow::editComponent);
    connect(_buttonDeleteComponent, &QPushButton::clicked, this, &MainWindow::deleteComponent);

    // Fill tables with data
    loadComponents();
    loadUsers();
    loadWarehouses();

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

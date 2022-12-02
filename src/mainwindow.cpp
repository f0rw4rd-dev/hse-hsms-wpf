#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "loginwindow.h"

#include "component.h"

#include "addcomponentdialog.h"
#include "editcomponentdialog.h"
#include "deletecomponentdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Adjust MainWindow
    setWindowTitle("HSMS");
    setFixedSize(1000, 600);

    // Init pointers to UI elements
    _buttonLoadComponents = findChild<QPushButton*>("buttonLoadComponents");
    _buttonAddComponent = findChild<QPushButton*>("buttonAddComponent");
    _buttonEditComponent = findChild<QPushButton*>("buttonEditComponent");
    _buttonDeleteComponent = findChild<QPushButton*>("buttonDeleteComponent");

    _stackedWidget = findChild<QStackedWidget*>("stackedWidget");

    // Open LoginWindow
    _stackedWidget->addWidget(new LoginWindow(this));
    _stackedWidget->setCurrentIndex(1);

    // Connections
    connect(_buttonLoadComponents, SIGNAL(clicked()), this, SLOT(loadComponents()));
    connect(_buttonAddComponent, SIGNAL(clicked()), this, SLOT(addComponent()));
    connect(_buttonEditComponent, SIGNAL(clicked()), this, SLOT(editComponent()));
    connect(_buttonDeleteComponent, SIGNAL(clicked()), this, SLOT(deleteComponent()));

    // Fill tables with data
    loadComponents();

    parentWidget();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadComponents()
{
    QTableWidget *tableComponents = findChild<QTableWidget*>("tableComponents");

    tableComponents->setRowCount(0);

    for (std::shared_ptr<DBComponent> &dbComponent : Component::getComponents()) {
        int row = tableComponents->rowCount();

        tableComponents->insertRow(row);

        tableComponents->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(dbComponent->typeName)));
        tableComponents->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(dbComponent->name)));
        tableComponents->setItem(row, 2, new QTableWidgetItem(QString::number(dbComponent->warranty)));
        tableComponents->setItem(row, 3, new QTableWidgetItem(QString::number(dbComponent->price)));
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

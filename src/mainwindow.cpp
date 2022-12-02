#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "loginwindow.h"

#include "component.h"

#include "addcomponentdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Adjust MainWindow
    setWindowTitle("HSMS");
    setFixedSize(1000, 600);

    // Init pointers to UI elements
    _buttonAddComponent = findChild<QPushButton*>("buttonAddComponent");
    _buttonLoadComponents = findChild<QPushButton*>("buttonLoadComponents");

    _stackedWidget = findChild<QStackedWidget*>("stackedWidget");

    // Open LoginWindow
    _stackedWidget->addWidget(new LoginWindow(this));
    _stackedWidget->setCurrentIndex(1);

    // Connectors
    connect(_buttonAddComponent, SIGNAL(clicked()), this, SLOT(addComponent()));
    connect(_buttonLoadComponents, SIGNAL(clicked()), this, SLOT(loadComponents()));

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
    AddComponentDialog *addComponentDialog = new AddComponentDialog;
    addComponentDialog->show();
}

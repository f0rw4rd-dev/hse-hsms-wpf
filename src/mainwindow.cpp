#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "loginwindow.h"

#include "component.h"

#include "dbconnection.h"

#include "addcomponentdialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("HSMS");
    setFixedSize(1000, 600);

    QPushButton *pbAddComponent = findChild<QPushButton*>("pbAddComponent");
    connect(pbAddComponent, SIGNAL(clicked()), this, SLOT(addComponent()));

    QStackedWidget *stackedWidget = findChild<QStackedWidget*>("stackedWidget");

    LoginWindow *loginWindow = new LoginWindow(this);

    stackedWidget->addWidget(loginWindow);
    stackedWidget->setCurrentIndex(1);

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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "loginwindow.h"

#include "dbconnection.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("HSMS");
    setFixedSize(1000, 600);

    //menuBar = findChild<QMenuBar*>("menubar");
    //menuBar->hide();

    QStackedWidget *stackedWidget = findChild<QStackedWidget*>("stackedWidget");

    LoginWindow *loginWindow = new LoginWindow(this);

    stackedWidget->addWidget(loginWindow);
    stackedWidget->setCurrentIndex(1);

    //todo
    QTableWidget *tableComponents = findChild<QTableWidget*>("tableComponents");

    //tableComponents->insertRow(0);
    //tableComponents->setItem(0, 1, new QTableWidgetItem("gsdgsd"));

    if (!dbConnection->isConnectionReliable()) {
        //todo handle
        return;
    }

    QString request = QString("SELECT * FROM components");
    for (auto [id, componentTypeId, name, warranty, price] : dbConnection->getTransaction()->query<int, int, std::string, int, float>(request.toStdString())) {
        int row = tableComponents->rowCount();

        tableComponents->insertRow(row);

        // проверить утечку памяти

        tableComponents->setItem(row, 0, new QTableWidgetItem(QString::number(id)));
        tableComponents->setItem(row, 1, new QTableWidgetItem(QString::number(componentTypeId)));
        tableComponents->setItem(row, 2, new QTableWidgetItem(QString::fromUtf8(name)));
        tableComponents->setItem(row, 3, new QTableWidgetItem(QString::number(warranty)));
        tableComponents->setItem(row, 4, new QTableWidgetItem(QString::number(price)));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "loginwindow.h"

#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("HSMS");
    setFixedSize(1000, 600);

    QStackedWidget *stackedWidget = findChild<QStackedWidget*>("stackedWidget");

    LoginWindow *loginWindow = new LoginWindow(this);

    stackedWidget->addWidget(loginWindow);
    stackedWidget->setCurrentIndex(2);
}

MainWindow::~MainWindow()
{
    delete ui;
}


#include "deletewarehousedialog.h"
#include "ui_deletewarehousedialog.h"
#include "warehouse.h"
#include "regularexpressions.h"

#include <QPushButton>
#include <QRegularExpressionValidator>
#include <QMessageBox>

DeleteWarehouseDialog::DeleteWarehouseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteWarehouseDialog)
{
    ui->setupUi(this);

    setWindowTitle("Удалить склад");

    // Init pointers to UI elements
    _buttonDeleteWarehouse = findChild<QPushButton*>("buttonDeleteWarehouse");
    _inputId = findChild<QLineEdit*>("inputId");

    // Validators
    _inputId->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));

    // Connections
    connect(_buttonDeleteWarehouse, &QPushButton::clicked, this, &DeleteWarehouseDialog::deleteWarehouse);
}

DeleteWarehouseDialog::~DeleteWarehouseDialog()
{
    delete ui;
}

void DeleteWarehouseDialog::deleteWarehouse()
{
    if (_inputId->text().isEmpty()) {
        QMessageBox::information(nullptr, "Предупреждение", "Заполните все поля!");
        return;
    }

    if (!Warehouse::doesWarehouseExist(_inputId->text().toInt())) {
        QMessageBox::information(nullptr, "Предупреждение", "Данного склада не существует!");
        return;
    }

    Warehouse::deleteWarehouse(_inputId->text().toInt());

    close();
    deleteLater();

    QMessageBox::information(nullptr, "Информация", "Склад удален!");
}

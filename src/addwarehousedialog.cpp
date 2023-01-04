#include "addwarehousedialog.h"
#include "ui_addwarehousedialog.h"
#include "warehouse.h"
#include "regularexpressions.h"

#include <QMessageBox>

AddWarehouseDialog::AddWarehouseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddWarehouseDialog)
{
    ui->setupUi(this);

    setWindowTitle("Добавить склад");

    // Init pointers to UI elements
    _buttonAddWarehouse = findChild<QPushButton*>("buttonAddWarehouse");
    _inputCity = findChild<QLineEdit*>("inputCity");
    _inputStreet = findChild<QLineEdit*>("inputStreet");
    _inputHouse = findChild<QLineEdit*>("inputHouse");
    _inputZip = findChild<QLineEdit*>("inputZip");

    // Validators
    _inputCity->setValidator(new QRegularExpressionValidator(RegularExpressions::address, this));
    _inputStreet->setValidator(new QRegularExpressionValidator(RegularExpressions::address, this));
    _inputHouse->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputZip->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));

    // Connections
    connect(_buttonAddWarehouse, &QPushButton::clicked, this, &AddWarehouseDialog::addWarehouse);
}

AddWarehouseDialog::~AddWarehouseDialog()
{
    delete ui;
}

void AddWarehouseDialog::addWarehouse()
{
    if (_inputCity->text().isEmpty() || _inputStreet->text().isEmpty() || _inputHouse->text().isEmpty() || _inputZip->text().isEmpty()) {
        QMessageBox::information(nullptr, "Предупреждение", "Заполните все поля!");
        return;
    }

    if (Warehouse::doesWarehouseExist(_inputCity->text(), _inputStreet->text(), _inputHouse->text().toInt(), _inputZip->text().toInt())) {
        QMessageBox::information(nullptr, "Предупреждение", "Склад с данным адресом уже существует!");
        return;
    }

    DBWarehouse dbWarehouse(_inputCity->text(), _inputStreet->text(), _inputHouse->text().toInt(), _inputZip->text().toInt());

    Warehouse::addWarehouse(dbWarehouse);

    close();
    deleteLater();

    QMessageBox::information(nullptr, "Информация", "Склад добавлен!");

}

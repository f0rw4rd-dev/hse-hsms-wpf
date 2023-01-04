#include "setwarehousedialog.h"
#include "ui_setwarehousedialog.h"
#include "regularexpressions.h"
#include "warehouse.h"

#include <QPushButton>
#include <QMessageBox>

SetWarehouseDialog::SetWarehouseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetWarehouseDialog)
{
    ui->setupUi(this);

    setWindowTitle("Изменить склад");

    // Init pointers to UI elements
    _buttonSetWarehouse = findChild<QPushButton*>("buttonSetWarehouse");
    _inputId = findChild<QLineEdit*>("inputId");
    _inputCity = findChild<QLineEdit*>("inputCity");
    _inputStreet = findChild<QLineEdit*>("inputStreet");
    _inputHouse = findChild<QLineEdit*>("inputHouse");
    _inputZip = findChild<QLineEdit*>("inputZip");

    // Validators
    _inputId->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputCity->setValidator(new QRegularExpressionValidator(RegularExpressions::address, this));
    _inputStreet->setValidator(new QRegularExpressionValidator(RegularExpressions::address, this));
    _inputHouse->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputZip->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));

    // Connections
    connect(_inputId, &QLineEdit::textChanged, this, &SetWarehouseDialog::loadWarehouse);
    connect(_buttonSetWarehouse, &QPushButton::clicked, this, &SetWarehouseDialog::setWarehouse);
}

SetWarehouseDialog::~SetWarehouseDialog()
{
    delete ui;
}

void SetWarehouseDialog::loadWarehouse(const QString &id)
{
    std::unique_ptr<DBWarehouse> dbWarehouse = Warehouse::getWarehouse(id.toInt());

    if (dbWarehouse == nullptr) {
        _inputCity->clear();
        _inputStreet->clear();
        _inputHouse->clear();
        _inputZip->clear();
        return;
    }

    _inputCity->setText(QString::fromStdString(dbWarehouse->city));
    _inputStreet->setText(QString::fromStdString(dbWarehouse->street));
    _inputHouse->setText(QString::number(dbWarehouse->house));
    _inputZip->setText(QString::number(dbWarehouse->zip));
}

void SetWarehouseDialog::setWarehouse()
{
    if (_inputId->text().isEmpty() || _inputCity->text().isEmpty() || _inputStreet->text().isEmpty() || _inputHouse->text().isEmpty() || _inputZip->text().isEmpty()) {
        QMessageBox::information(nullptr, "Предупреждение", "Заполните все поля!");
        return;
    }

    if (!Warehouse::doesWarehouseExist(_inputId->text().toInt())) {
        QMessageBox::information(nullptr, "Предупреждение", "Данного склада не существует!");
        return;
    }

    DBWarehouse dbWarehouse(_inputId->text().toInt(), _inputCity->text().toStdString(), _inputStreet->text().toStdString(), _inputHouse->text().toInt(), _inputZip->text().toInt());
    Warehouse::setWarehouse(dbWarehouse);

    close();
    deleteLater();

    QMessageBox::information(nullptr, "Информация", "Информация о складе изменена!");
}

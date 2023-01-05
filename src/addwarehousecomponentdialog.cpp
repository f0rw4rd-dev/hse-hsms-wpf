#include "addwarehousecomponentdialog.h"
#include "ui_addwarehousecomponentdialog.h"
#include "warehousecomponent.h"
#include "regularexpressions.h"

#include <QRegularExpressionValidator>
#include <QPushButton>
#include <QMessageBox>

AddWarehouseComponentDialog::AddWarehouseComponentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddWarehouseComponentDialog)
{
    ui->setupUi(this);

    setWindowTitle("Добавить комплектующее на склад");

    // Init pointers to UI elements
    _buttonAddWarehouseComponent = findChild<QPushButton*>("buttonAddWarehouseComponent");
    _inputComponentId = findChild<QLineEdit*>("inputComponentId");
    _inputWarehouseId = findChild<QLineEdit*>("inputWarehouseId");
    _inputAmount = findChild<QLineEdit*>("inputAmount");

    // Validators
    _inputComponentId->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputWarehouseId->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputAmount->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));

    // Connections
    connect(_buttonAddWarehouseComponent, &QPushButton::clicked, this, &AddWarehouseComponentDialog::addWarehouseComponent);
}

AddWarehouseComponentDialog::~AddWarehouseComponentDialog()
{
    delete ui;
}

void AddWarehouseComponentDialog::addWarehouseComponent()
{
    if (_inputComponentId->text().isEmpty() || _inputWarehouseId->text().isEmpty() || _inputAmount->text().isEmpty()) {
        QMessageBox::information(nullptr, "Предупреждение", "Заполните все поля!");
        return;
    }

    if (!Component::doesComponentExist(_inputComponentId->text().toInt())) {
        QMessageBox::information(nullptr, "Предупреждение", "Данного комплектующего не существует!");
        return;
    }

    if (!Warehouse::doesWarehouseExist(_inputWarehouseId->text().toInt())) {
        QMessageBox::information(nullptr, "Предупреждение", "Данного склада не существует!");
        return;
    }

    if (WarehouseComponent::doesWarehouseComponentExist(_inputComponentId->text().toInt(), _inputWarehouseId->text().toInt())) {
        QMessageBox::information(nullptr, "Предупреждение", "Комплектующее на данном складе уже имеется!");
        return;
    }

    WarehouseComponent warehouseComponent(_inputWarehouseId->text().toInt(), _inputComponentId->text().toInt(), _inputAmount->text().toInt());
    WarehouseComponent::addWarehouseComponent(warehouseComponent);

    close();
    deleteLater();

    QMessageBox::information(nullptr, "Информация", "Комплектующее на склад добавлено!");
}

#include "deletewarehousecomponentdialog.h"
#include "ui_deletewarehousecomponentdialog.h"
#include "warehousecomponent.h"
#include "regularexpressions.h"

#include <QRegularExpressionValidator>
#include <QPushButton>
#include <QMessageBox>

DeleteWarehouseComponentDialog::DeleteWarehouseComponentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteWarehouseComponentDialog)
{
    ui->setupUi(this);

    setWindowTitle("Удалить информацию о комплектующем на складе");

    // Init pointers to UI elements
    _buttonDeleteWarehouseComponent = findChild<QPushButton*>("buttonDeleteWarehouseComponent");
    _inputComponentId = findChild<QLineEdit*>("inputComponentId");
    _inputWarehouseId = findChild<QLineEdit*>("inputWarehouseId");

    // Validators
    _inputComponentId->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputWarehouseId->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));

    // Connections
    connect(_buttonDeleteWarehouseComponent, &QPushButton::clicked, this, &DeleteWarehouseComponentDialog::deleteWarehouseComponent);
}

DeleteWarehouseComponentDialog::~DeleteWarehouseComponentDialog()
{
    delete ui;
}

void DeleteWarehouseComponentDialog::deleteWarehouseComponent()
{
    if (_inputComponentId->text().isEmpty() || _inputWarehouseId->text().isEmpty()) {
        QMessageBox::information(nullptr, "Предупреждение", "Заполните все поля!");
        return;
    }

    if (!WarehouseComponent::doesWarehouseComponentExist(_inputComponentId->text().toInt(), _inputWarehouseId->text().toInt())) {
        QMessageBox::information(nullptr, "Предупреждение", "Комплектующего на данном складе нет!");
        return;
    }

    WarehouseComponent::deleteWarehouseComponent(_inputComponentId->text().toInt(), _inputWarehouseId->text().toInt());

    close();
    deleteLater();

    QMessageBox::information(nullptr, "Информация", "Информация о комплектующем на складе удалена!");
}

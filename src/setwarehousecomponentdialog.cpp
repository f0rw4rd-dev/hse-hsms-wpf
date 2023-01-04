#include "setwarehousecomponentdialog.h"
#include "ui_setwarehousecomponentdialog.h"
#include "warehousecomponent.h"
#include "regularexpressions.h"

#include <QRegularExpressionValidator>
#include <QPushButton>
#include <QMessageBox>

SetWarehouseComponentDialog::SetWarehouseComponentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetWarehouseComponentDialog)
{
    ui->setupUi(this);

    setWindowTitle("Изменить информацию о комплектующем на складе");

    // Init pointers to UI elements
    _buttonSetWarehouseComponent = findChild<QPushButton*>("buttonSetWarehouseComponent");
    _inputComponentId = findChild<QLineEdit*>("inputComponentId");
    _inputWarehouseId = findChild<QLineEdit*>("inputWarehouseId");
    _inputAmount = findChild<QLineEdit*>("inputAmount");

    // Validators
    _inputComponentId->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputWarehouseId->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputAmount->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));

    // Connections
    connect(_inputComponentId, &QLineEdit::textChanged, this, &SetWarehouseComponentDialog::loadWarehouseComponent);
    connect(_inputWarehouseId, &QLineEdit::textChanged, this, &SetWarehouseComponentDialog::loadWarehouseComponent);
    connect(_buttonSetWarehouseComponent, &QPushButton::clicked, this, &SetWarehouseComponentDialog::setWarehouseComponent);
}

SetWarehouseComponentDialog::~SetWarehouseComponentDialog()
{
    delete ui;
}

void SetWarehouseComponentDialog::loadWarehouseComponent(const QString&)
{
    QScopedPointer<DBWarehouseComponent> dbWarehouseComponent = WarehouseComponent::getWarehouseComponent(_inputComponentId->text().toInt(), _inputWarehouseId->text().toInt());

    if (dbWarehouseComponent == nullptr) {
        _inputAmount->clear();
        return;
    }

    _inputAmount->setText(QString::number(dbWarehouseComponent->amount));
}

void SetWarehouseComponentDialog::setWarehouseComponent()
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

    if (!WarehouseComponent::doesWarehouseComponentExist(_inputComponentId->text().toInt(), _inputWarehouseId->text().toInt())) {
        QMessageBox::information(nullptr, "Предупреждение", "Комплектующего на данном складе нет!");
        return;
    }

    DBWarehouseComponent dbWarehouseComponent(_inputWarehouseId->text().toInt(), _inputComponentId->text().toInt(), _inputAmount->text().toInt());
    WarehouseComponent::setWarehouseComponent(dbWarehouseComponent);

    close();
    deleteLater();

    QMessageBox::information(nullptr, "Информация", "Информация о комплектующем на складе изменена!");
}

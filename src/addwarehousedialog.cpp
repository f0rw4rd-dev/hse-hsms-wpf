#include "addwarehousedialog.h"
#include "ui_addwarehousedialog.h"
#include "warehouse.h"

AddWarehouseDialog::AddWarehouseDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddWarehouseDialog)
{
    ui->setupUi(this);

    setWindowTitle("Добавить склад");

    // Init pointers to UI elements
    _buttonAddWarehouse = findChild<QPushButton*>("buttonAddWarehouse");
    _inputAddress = findChild<QLineEdit*>("inputAddress");

    // Validators
    QRegularExpression addressRegExp("[a-zA-Zа-яА-Я0-9.;, ]+");
    _inputAddress->setValidator(new QRegularExpressionValidator(addressRegExp, this));

    // Connections
    connect(_buttonAddWarehouse, &QPushButton::clicked, this, &AddWarehouseDialog::addWarehouse);
}

AddWarehouseDialog::~AddWarehouseDialog()
{
    delete ui;
}

void AddWarehouseDialog::addWarehouse()
{
    if (_inputAddress->text().isEmpty()) {
        //todo handle
        return;
    }

    DBWarehouse dbWarehouse(-1, _inputAddress->text().toStdString());

    Warehouse::addWarehouse(dbWarehouse);
}

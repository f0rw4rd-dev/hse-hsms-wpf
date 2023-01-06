#include "addcomputerdialog.h"
#include "ui_addcomputerdialog.h"
#include "regularexpressions.h"

#include <QRegularExpressionValidator>

AddComputerDialog::AddComputerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddComputerDialog)
{
    ui->setupUi(this);

    setWindowTitle("Добавить сборку ПК");

    // Init pointers to UI elements
    _buttonAddComputer = findChild<QPushButton*>("buttonAddComputer");
    _inputCPUId = findChild<QLineEdit*>("inputCPUId");
    _inputCPUName = findChild<QLineEdit*>("inputCPUName");
    _inputMotherboardId = findChild<QLineEdit*>("inputMotherboardId");
    _inputMotherboardName = findChild<QLineEdit*>("inputMotherboardName");
    _inputVideocardId = findChild<QLineEdit*>("inputVideocardId");
    _inputVideocardName = findChild<QLineEdit*>("inputVideocardName");
    _inputRAMId = findChild<QLineEdit*>("inputRAMId");
    _inputRAMName = findChild<QLineEdit*>("inputRAMName");
    _inputRAMAmount = findChild<QLineEdit*>("inputRAMAmount");
    _inputCaseId = findChild<QLineEdit*>("inputCaseId");
    _inputCaseName = findChild<QLineEdit*>("inputCaseName");
    _inputPSUId = findChild<QLineEdit*>("inputPSUId");
    _inputPSUName = findChild<QLineEdit*>("inputPSUName");
    _inputHDDId = findChild<QLineEdit*>("inputHDDId");
    _inputHDDName = findChild<QLineEdit*>("inputHDDName");
    _inputHDDAmount = findChild<QLineEdit*>("inputHDDAmount");
    _inputSSDId = findChild<QLineEdit*>("inputSSDId");
    _inputSSDName = findChild<QLineEdit*>("inputSSDName");
    _inputSSDAmount = findChild<QLineEdit*>("inputSSDAmount");
    _inputSSDM2Id = findChild<QLineEdit*>("inputSSDM2Id");
    _inputSSDM2Name = findChild<QLineEdit*>("inputSSDM2Name");
    _inputSSDM2Amount = findChild<QLineEdit*>("inputSSDM2Amount");
    _inputFanId = findChild<QLineEdit*>("inputFanId");
    _inputFanName = findChild<QLineEdit*>("inputFanName");
    _inputFanAmount = findChild<QLineEdit*>("inputFanAmount");
    _inputWCSId = findChild<QLineEdit*>("inputWCSId");
    _inputWCSName = findChild<QLineEdit*>("inputWCSName");
    _inputCoolerId = findChild<QLineEdit*>("inputCoolerId");
    _inputCoolerName = findChild<QLineEdit*>("inputCoolerName");

    // Validators
    _inputCPUId->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputMotherboardId->setValidator(new QRegularExpressionValidator(RegularExpressions::address, this));
    _inputVideocardId->setValidator(new QRegularExpressionValidator(RegularExpressions::address, this));
    _inputRAMId->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputRAMAmount->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputCaseId->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputPSUId->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputHDDId->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputHDDAmount->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputSSDId->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputSSDAmount->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputSSDM2Id->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputSSDM2Amount->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputFanId->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputFanAmount->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputWCSId->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputCoolerId->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));

    // Connections
    //connect(_inputId, &QLineEdit::textChanged, this, &SetWarehouseDialog::loadWarehouse);
    connect(_buttonAddComputer, &QPushButton::clicked, this, &AddComputerDialog::addComputer);
}

AddComputerDialog::~AddComputerDialog()
{
    delete ui;
}

void AddComputerDialog::loadCpu(const QString &id)
{

}


void AddComputerDialog::addComputer()
{

}


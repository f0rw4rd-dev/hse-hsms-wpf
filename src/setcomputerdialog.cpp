#include "setcomputerdialog.h"
#include "ui_setcomputerdialog.h"
#include "regularexpressions.h"
#include "component.h"
#include "computer.h"

#include <QRegularExpressionValidator>
#include <QMessageBox>

SetComputerDialog::SetComputerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetComputerDialog)
{
    ui->setupUi(this);

    setWindowTitle("Изменить сборку компьютера");

    // Init pointers to UI elements
    _buttonSetComputer = findChild<QPushButton*>("buttonSetComputer");
    _inputId = findChild<QLineEdit*>("inputId");
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
    connect(_buttonSetComputer, &QPushButton::clicked, this, &SetComputerDialog::setComputer);
    connect(_inputId, &QLineEdit::textChanged, this, &SetComputerDialog::loadComputer);
    connect(_inputCPUId, &QLineEdit::textChanged, this, [this](const QString &id){ loadComponent(id, _inputCPUName, "Процессор"); });
    connect(_inputMotherboardId, &QLineEdit::textChanged, this, [this](const QString &id){ loadComponent(id, _inputMotherboardName, "Материнская плата"); });
    connect(_inputVideocardId, &QLineEdit::textChanged, this, [this](const QString &id){ loadComponent(id, _inputVideocardName, "Видеокарта"); });
    connect(_inputRAMId, &QLineEdit::textChanged, this, [this](const QString &id){ loadComponent(id, _inputRAMName, "Оперативная память"); });
    connect(_inputCaseId, &QLineEdit::textChanged, this, [this](const QString &id){ loadComponent(id, _inputCaseName, "Корпус"); });
    connect(_inputPSUId, &QLineEdit::textChanged, this, [this](const QString &id){ loadComponent(id, _inputPSUName, "Блок питания"); });
    connect(_inputHDDId, &QLineEdit::textChanged, this, [this](const QString &id){ loadComponent(id, _inputHDDName, "Жесткий диск"); });
    connect(_inputSSDId, &QLineEdit::textChanged, this, [this](const QString &id){ loadComponent(id, _inputSSDName, "SSD накопитель"); });
    connect(_inputSSDM2Id, &QLineEdit::textChanged, this, [this](const QString &id){ loadComponent(id, _inputSSDM2Name, "SSD M.2 накопитель"); });
    connect(_inputFanId, &QLineEdit::textChanged, this, [this](const QString &id){ loadComponent(id, _inputFanName, "Вентилятор для корпуса"); });
    connect(_inputWCSId, &QLineEdit::textChanged, this, [this](const QString &id){ loadComponent(id, _inputWCSName, "Система водяного охлаждения"); });
    connect(_inputCoolerId, &QLineEdit::textChanged, this, [this](const QString &id){ loadComponent(id, _inputCoolerName, "Кулер для процессора"); });
}

SetComputerDialog::~SetComputerDialog()
{
    delete ui;
}

void SetComputerDialog::loadComponent(const QString id, QLineEdit *inputName, const QString componentTypeName)
{
    QSharedPointer<Component> component = Component::getComponent(id.toInt());

    if (component == nullptr || component->componentType->name != componentTypeName) {
        inputName->clear();
        return;
    }

    inputName->setText(component->name);
}

void SetComputerDialog::loadComputer(const QString &id)
{
    QSharedPointer<Computer> computer = Computer::getComputer(id.toInt());

    if (computer.isNull()) {
        _inputCPUId->clear();
        _inputCPUName->clear();
        _inputMotherboardId->clear();
        _inputMotherboardName->clear();
        _inputVideocardId->clear();
        _inputVideocardName->clear();
        _inputRAMId->clear();
        _inputRAMName->clear();
        _inputRAMAmount->clear();
        _inputCaseId->clear();
        _inputCaseName->clear();
        _inputPSUId->clear();
        _inputPSUName->clear();
        _inputHDDId->clear();
        _inputHDDName->clear();
        _inputHDDAmount->clear();
        _inputSSDId->clear();
        _inputSSDName->clear();
        _inputSSDAmount->clear();
        _inputSSDM2Id->clear();
        _inputSSDM2Name->clear();
        _inputSSDM2Amount->clear();
        _inputFanId->clear();
        _inputFanName->clear();
        _inputFanAmount->clear();
        _inputWCSId->clear();
        _inputWCSName->clear();
        _inputCoolerId->clear();
        _inputCoolerName->clear();
        return;
    }

    _inputCPUId->setText(QString::number(computer->cpu->id));
    _inputMotherboardId->setText(QString::number(computer->motherboard->id));

    if (computer->videocard->id >= 1) {
        _inputVideocardId->setText(QString::number(computer->videocard->id));
    }

    _inputRAMId->setText(QString::number(computer->ram->id));
    _inputRAMAmount->setText(QString::number(computer->ram->amount));
    _inputCaseId->setText(QString::number(computer->chassis->id));
    _inputPSUId->setText(QString::number(computer->psu->id));

    if (!computer->hdd.isNull()) {
        _inputHDDId->setText(QString::number(computer->hdd->id));
        _inputHDDAmount->setText(QString::number(computer->hdd->amount));
    }

    if (!computer->ssd.isNull()) {
        _inputSSDId->setText(QString::number(computer->ssd->id));
        _inputSSDAmount->setText(QString::number(computer->ssd->amount));
    }

    if (!computer->ssdM2.isNull()) {
        _inputSSDM2Id->setText(QString::number(computer->ssdM2->id));
        _inputSSDM2Amount->setText(QString::number(computer->ssdM2->amount));
    }

    if (!computer->fan.isNull()) {
        _inputFanId->setText(QString::number(computer->fan->id));
        _inputFanAmount->setText(QString::number(computer->fan->amount));

    }

    if (!computer->wcs.isNull()) {
        _inputWCSId->setText(QString::number(computer->wcs->id));
    }

    if (!computer->cooler.isNull()) {
        _inputCoolerId->setText(QString::number(computer->cooler->id));
    }
}

void SetComputerDialog::setComputer()
{
    if (_inputId->text().isEmpty()) {
        QMessageBox::information(nullptr, "Предупреждение", "Заполните поле ИД!");
        return;
    }

    if (!Computer::doesComputerExist(_inputId->text().toInt())) {
        QMessageBox::information(nullptr, "Предупреждение", "Данная сборка компьютера не существует!");
        return;
    }

    //todo check videocard or gpu in cpu
    //todo check on empty fields

    auto getComponentId = [](QLineEdit *input){ return (input->text().isEmpty()) ? -1 : input->text().toInt(); };
    auto getComponentAmount = [](QLineEdit *input){ return (input->text().isEmpty()) ? 0 : input->text().toInt(); };

    Computer computer(getComponentId(_inputCPUId), getComponentId(_inputMotherboardId), getComponentId(_inputVideocardId), getComponentId(_inputRAMId),
                      getComponentAmount(_inputRAMAmount), getComponentId(_inputCaseId), getComponentId(_inputPSUId), getComponentId(_inputHDDId),
                      getComponentAmount(_inputHDDAmount), getComponentId(_inputSSDId), getComponentAmount(_inputSSDAmount), getComponentId(_inputSSDM2Id),
                      getComponentAmount(_inputSSDM2Amount), getComponentId(_inputFanId), getComponentAmount(_inputFanAmount), getComponentId(_inputWCSId),
                      getComponentId(_inputCoolerId));
    computer.id = _inputId->text().toInt();
    Computer::setComputer(computer);

    close();
    deleteLater();

    QMessageBox::information(nullptr, "Информация", "Сборка компьютера изменена!");
}

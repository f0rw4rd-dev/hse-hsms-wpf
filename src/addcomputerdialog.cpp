#include "addcomputerdialog.h"
#include "ui_addcomputerdialog.h"
#include "regularexpressions.h"
#include "component.h"
#include "computer.h"

#include <QRegularExpressionValidator>
#include <QMessageBox>

AddComputerDialog::AddComputerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddComputerDialog)
{
    ui->setupUi(this);

    setWindowTitle("Добавить сборку компьютера");

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
    connect(_buttonAddComputer, &QPushButton::clicked, this, &AddComputerDialog::addComputer);
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

AddComputerDialog::~AddComputerDialog()
{
    delete ui;
}

void AddComputerDialog::loadComponent(const QString id, QLineEdit *inputName, const QString componentTypeName)
{
    QSharedPointer<Component> component = Component::getComponent(id.toInt());

    if (component == nullptr || component->componentType->name != componentTypeName) {
        inputName->clear();
        return;
    }

    inputName->setText(component->name);
}

void AddComputerDialog::addComputer()
{
    if (_inputCPUId->text().isEmpty() || _inputMotherboardId->text().isEmpty() || _inputRAMId->text().isEmpty()
            || _inputRAMAmount->text().isEmpty() || _inputCaseId->text().isEmpty() || _inputPSUId->text().isEmpty()) {
        QMessageBox::information(nullptr, "Предупреждение", "Поля: ИД процессора, ИД материнской платы, ИД оперативной памяти, Количество оперативной памяти, ИД корпуса, ИД блока питания являются обязательными!");
        return;
    }

    if (_inputRAMAmount->text().toInt() < 1) {
        QMessageBox::information(nullptr, "Предупреждение", "Количество оперативной памяти должно быть не менее 1!");
        return;
    }

    if (_inputHDDId->text().isEmpty() && _inputSSDId->text().isEmpty() && _inputSSDM2Id->text().isEmpty()) {
        QMessageBox::information(nullptr, "Предупреждение", "В сборке должен присутствовать как минимум один накопитель (HDD/SSD/SSD M.2)!");
        return;
    }

    if (_inputHDDId->text().isEmpty() && _inputSSDId->text().isEmpty() && _inputSSDM2Id->text().isEmpty()) {
        QMessageBox::information(nullptr, "Предупреждение", "В сборке должен присутствовать как минимум один накопитель (HDD/SSD/SSD M.2)!");
        return;
    }

    if (!_inputHDDId->text().isEmpty() && (_inputHDDAmount->text().isEmpty() || _inputHDDAmount->text().toInt() < 1)) {
        QMessageBox::information(nullptr, "Предупреждение", "Количество HDD накопителей не может быть меньше 1 (если HDD накопитель не требуется, то удалите его ИД)!");
        return;
    }

    if (!_inputSSDId->text().isEmpty() && (_inputSSDAmount->text().isEmpty() || _inputSSDAmount->text().toInt() < 1)) {
        QMessageBox::information(nullptr, "Предупреждение", "Количество SSD накопителей не может быть меньше 1 (если SSD накопитель не требуется, то удалите его ИД)!");
        return;
    }

    if (!_inputSSDM2Id->text().isEmpty() && (_inputSSDM2Amount->text().isEmpty() || _inputSSDM2Amount->text().toInt() < 1)) {
        QMessageBox::information(nullptr, "Предупреждение", "Количество SSD M.2 накопителей не может быть меньше 1 (если SSD M.2 накопитель не требуется, то удалите его ИД)!");
        return;
    }

    if (_inputWCSId->text().isEmpty() && _inputCoolerId->text().isEmpty()) {
        QMessageBox::information(nullptr, "Предупреждение", "В сборке должен присутствовать кулер или система жидкостного охлаждения!");
        return;
    }

    if (!_inputWCSId->text().isEmpty() && !_inputCoolerId->text().isEmpty()) {
        QMessageBox::information(nullptr, "Предупреждение", "В сборке не может одновременно присутствовать кулер и система жидкостного охлаждения (Кулер и СЖО используются для охлаждения процессора)!");
        return;
    }

    auto doesComponentExist = [](QLineEdit *input){ return Component::doesComponentExist(input->text().toInt()); };

    if (!doesComponentExist(_inputCPUId) || !doesComponentExist(_inputMotherboardId) || !doesComponentExist(_inputRAMId) || !doesComponentExist(_inputCaseId) || !doesComponentExist(_inputPSUId)) {
        QMessageBox::information(nullptr, "Предупреждение", "Одно или несколько из следующих комплектующих не существует: Процессор, Материнская плата, Оперативная память, Корпус, Блок питания!");
        return;
    }

    if ((!_inputHDDId->text().isEmpty() && !doesComponentExist(_inputHDDId))
            || (!_inputSSDId->text().isEmpty() && !doesComponentExist(_inputSSDId))
            || (!_inputSSDM2Id->text().isEmpty() && !doesComponentExist(_inputSSDM2Id))
            || (!_inputWCSId->text().isEmpty() && !doesComponentExist(_inputWCSId))
            || (!_inputCoolerId->text().isEmpty() && !doesComponentExist(_inputCoolerId))
            || (!_inputVideocardId->text().isEmpty() && !doesComponentExist(_inputVideocardId))) {
        QMessageBox::information(nullptr, "Предупреждение", "Одно или несколько из следующих комплектующих не существует: HDD, SSD, SSD M.2, СЖО, Кулер, Видеокарта!");
        return;
    }

    //todo check videocard or gpu in cpu

    auto getComponentId = [](QLineEdit *input){ return (input->text().isEmpty()) ? -1 : input->text().toInt(); };
    auto getComponentAmount = [](QLineEdit *input){ return (input->text().isEmpty()) ? 0 : input->text().toInt(); };

    Computer computer(getComponentId(_inputCPUId), getComponentId(_inputMotherboardId), getComponentId(_inputVideocardId), getComponentId(_inputRAMId),
                      getComponentAmount(_inputRAMAmount), getComponentId(_inputCaseId), getComponentId(_inputPSUId), getComponentId(_inputHDDId),
                      getComponentAmount(_inputHDDAmount), getComponentId(_inputSSDId), getComponentAmount(_inputSSDAmount), getComponentId(_inputSSDM2Id),
                      getComponentAmount(_inputSSDM2Amount), getComponentId(_inputFanId), getComponentAmount(_inputFanAmount), getComponentId(_inputWCSId),
                      getComponentId(_inputCoolerId));
    Computer::addComputer(computer);

    close();
    deleteLater();

    QMessageBox::information(nullptr, "Информация", "Сборка компьютера добавлена!");
}


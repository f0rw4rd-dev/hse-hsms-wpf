#include "setcomponentdialog.h"
#include "ui_setcomponentdialog.h"
#include "component.h"

#include <QMessageBox>

SetComponentDialog::SetComponentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetComponentDialog)
{
    ui->setupUi(this);

    setWindowTitle("Изменить комплектующее");

    // Init pointers to UI elements
    _buttonSetComponent = findChild<QPushButton*>("buttonSetComponent");
    _comboTypeName = findChild<QComboBox*>("comboTypeName");
    _inputId = findChild<QLineEdit*>("inputId");
    _inputName = findChild<QLineEdit*>("inputName");
    _inputWarranty = findChild<QLineEdit*>("inputWarranty");
    _inputPrice = findChild<QLineEdit*>("inputPrice");

    // Validators
    QRegularExpression nameRegExp("[a-zA-Zа-яА-Я0-9(), ]+");

    QLocale locale(QLocale::English, QLocale::UnitedStates);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);

    QDoubleValidator *doubleValidator = new QDoubleValidator(0,  std::numeric_limits<float>::max(), 2, this);
    doubleValidator->setLocale(locale);

    _inputId->setValidator(new QIntValidator(1, std::numeric_limits<int>::max(), this));
    _inputName->setLocale(locale);
    _inputName->setValidator(new QRegularExpressionValidator(nameRegExp, this));
    _inputWarranty->setValidator(new QIntValidator(1, std::numeric_limits<int>::max(), this));
    _inputPrice->setValidator(doubleValidator);

    // Connections
    connect(_inputId, &QLineEdit::textChanged, this, &SetComponentDialog::loadComponent);
    connect(_buttonSetComponent, &QPushButton::clicked, this, &SetComponentDialog::setComponent);

    //todo: load type components
    loadComponentTypes();
}

SetComponentDialog::~SetComponentDialog()
{
    delete ui;
}

void SetComponentDialog::loadComponentTypes()
{
    _comboTypeName->clear();

    for (pqxx::row const &row : Component::getComponentTypes())
        _comboTypeName->addItem(QString::fromStdString(row[1].c_str()), QVariant(atoi(row[0].c_str())));
}

void SetComponentDialog::loadComponent(const QString &id)
{
    std::unique_ptr<DBComponent> dbComponent = Component::getComponent(id.toInt());

    if (dbComponent == nullptr) {
        loadComponentTypes();

        _inputName->clear();
        _inputWarranty->clear();
        _inputPrice->clear();
        return;
    }

    _comboTypeName->setCurrentIndex(_comboTypeName->findData(QVariant(dbComponent->typeId)));
    _inputName->setText(QString::fromStdString(dbComponent->name));
    _inputWarranty->setText(QString::number(dbComponent->warranty));
    _inputPrice->setText(QString::number(dbComponent->price));
}

void SetComponentDialog::setComponent()
{
    if (_inputId->text().isEmpty() || _inputName->text().isEmpty() || _inputWarranty->text().isEmpty() || _inputPrice->text().isEmpty()) {
        QMessageBox::information(nullptr, "Предупреждение", "Заполните все поля!");
        return;
    }

    if (!Component::doesComponentExist(_inputId->text().toInt())) {
        QMessageBox::information(nullptr, "Предупреждение", "Данного комплектующего нет!");
        return;
    }

    DBComponent dbComponent(_inputId->text().toInt(), _inputName->text().toStdString(), _comboTypeName->itemData(_comboTypeName->currentIndex()).toInt(), _comboTypeName->currentText().toStdString(), _inputWarranty->text().toInt(), _inputPrice->text().toDouble());
    Component::setComponent(dbComponent);

    close();
}

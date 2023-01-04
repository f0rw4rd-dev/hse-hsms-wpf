#include "addcomponentdialog.h"
#include "ui_addcomponentdialog.h"

#include "component.h"
#include "componenttype.h"
#include "regularexpressions.h"

#include <QVariant>
#include <QMessageBox>

AddComponentDialog::AddComponentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddComponentDialog)
{
    ui->setupUi(this);

    setWindowTitle("Добавить комплектующее");

    // Init pointers to UI elements
    _buttonAddComponent = findChild<QPushButton*>("buttonAddComponent");
    _comboTypeName = findChild<QComboBox*>("comboTypeName");
    _inputName = findChild<QLineEdit*>("inputName");
    _inputWarranty = findChild<QLineEdit*>("inputWarranty");
    _inputPrice = findChild<QLineEdit*>("inputPrice");

    // Validators
    QLocale locale(QLocale::English, QLocale::UnitedStates);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);

    QDoubleValidator *doubleValidator = new QDoubleValidator(0,  std::numeric_limits<float>::max(), 2, this);
    doubleValidator->setLocale(locale);

    _inputName->setLocale(locale);
    _inputName->setValidator(new QRegularExpressionValidator(RegularExpressions::componentName, this));
    _inputWarranty->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputPrice->setValidator(doubleValidator);

    // Connections
    connect(_buttonAddComponent, &QPushButton::clicked, this, &AddComponentDialog::addComponent);

    // Fill the QComboBox with component types
    loadComponentTypes();
}

AddComponentDialog::~AddComponentDialog()
{
    delete ui;
}

void AddComponentDialog::loadComponentTypes()
{
    _comboTypeName->clear();

    for (const auto &row : ComponentType::getComponentTypes())
        _comboTypeName->addItem(row->name, QVariant(row->id));
}

void AddComponentDialog::addComponent()
{
    if (_inputName->text().isEmpty() || _inputWarranty->text().isEmpty() || _inputPrice->text().isEmpty()) {
        QMessageBox::information(nullptr, "Предупреждение", "Заполните все поля!");
        return;
    }

    if (Component::doesComponentExist(_inputName->text())) {
        QMessageBox::information(nullptr, "Предупреждение", "Комплектующее с данным названием уже существует!");
        return;
    }

    DBComponent dbComponent(_inputName->text(), _comboTypeName->itemData(_comboTypeName->currentIndex()).toInt(), _comboTypeName->currentText(), _inputWarranty->text().toInt(), _inputPrice->text().toFloat());

    Component::addComponent(dbComponent);

    close();
    deleteLater();

    QMessageBox::information(nullptr, "Информация", "Комплектующее добавлено!");
}

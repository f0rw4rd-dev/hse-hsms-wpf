#include "setcomponentdialog.h"
#include "ui_setcomponentdialog.h"
#include "component.h"
#include "componenttype.h"
#include "regularexpressions.h"

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

    QLocale locale(QLocale::English, QLocale::UnitedStates);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);

    QDoubleValidator *doubleValidator = new QDoubleValidator(0,  std::numeric_limits<float>::max(), 2, this);
    doubleValidator->setLocale(locale);

    _inputId->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputName->setLocale(locale);
    _inputName->setValidator(new QRegularExpressionValidator(RegularExpressions::componentName, this));
    _inputWarranty->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputPrice->setValidator(doubleValidator);

    // Connections
    connect(_inputId, &QLineEdit::textChanged, this, &SetComponentDialog::loadComponent);
    connect(_buttonSetComponent, &QPushButton::clicked, this, &SetComponentDialog::setComponent);

    loadComponentTypes();
}

SetComponentDialog::~SetComponentDialog()
{
    delete ui;
}

void SetComponentDialog::loadComponentTypes()
{
    _comboTypeName->clear();

    for (const auto &row : ComponentType::getComponentTypes())
        _comboTypeName->addItem(row->name, QVariant(row->id));
}

void SetComponentDialog::loadComponent(const QString &id)
{
    QScopedPointer<DBComponent> dbComponent = Component::getComponent(id.toInt());

    if (dbComponent == nullptr) {
        loadComponentTypes();

        _inputName->clear();
        _inputWarranty->clear();
        _inputPrice->clear();
        return;
    }

    _comboTypeName->setCurrentIndex(_comboTypeName->findData(QVariant(dbComponent->componentType->id)));
    _inputName->setText(dbComponent->name);
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

    DBComponent dbComponent(_inputId->text().toInt(), _inputName->text(), _comboTypeName->itemData(_comboTypeName->currentIndex()).toInt(), _comboTypeName->currentText(), _inputWarranty->text().toInt(), _inputPrice->text().toDouble());
    Component::setComponent(dbComponent);

    close();
    deleteLater();

    QMessageBox::information(nullptr, "Информация", "Информация о комплектующем изменена!");
}

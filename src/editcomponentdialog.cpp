#include "editcomponentdialog.h"
#include "ui_editcomponentdialog.h"
#include "component.h"

EditComponentDialog::EditComponentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditComponentDialog)
{
    ui->setupUi(this);

    setWindowTitle("Изменить комплектующее");

    // Init pointers to UI elements
    _buttonEditComponent = findChild<QPushButton*>("buttonEditComponent");
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
    connect(_inputId, &QLineEdit::textChanged, this, &EditComponentDialog::loadComponent);
    connect(_buttonEditComponent, &QPushButton::clicked, this, &EditComponentDialog::editComponent);

    //todo: load type components
    loadComponentTypes();
}

EditComponentDialog::~EditComponentDialog()
{
    delete ui;
}

void EditComponentDialog::loadComponentTypes()
{
    _comboTypeName->clear();

    for (pqxx::row const &row : Component::getComponentTypes())
        _comboTypeName->addItem(QString::fromStdString(row[1].c_str()), QVariant(atoi(row[0].c_str())));
}

void EditComponentDialog::loadComponent(const QString &id)
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

void EditComponentDialog::editComponent()
{
    DBComponent dbComponent(_inputId->text().toInt(), _inputName->text().toStdString(), _comboTypeName->itemData(_comboTypeName->currentIndex()).toInt(), _comboTypeName->currentText().toStdString(), _inputWarranty->text().toInt(), _inputPrice->text().toDouble());
    Component::editComponent(dbComponent);
}

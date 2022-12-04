#include "addcomponentdialog.h"
#include "ui_addcomponentdialog.h"

#include "component.h"

#include <QVariant>

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
    QRegularExpression nameRegExp("[a-zA-Zа-яА-Я0-9(), ]+");

    QLocale locale(QLocale::English, QLocale::UnitedStates);
    locale.setNumberOptions(QLocale::RejectGroupSeparator);

    QDoubleValidator *doubleValidator = new QDoubleValidator(0,  std::numeric_limits<float>::max(), 2, this);
    doubleValidator->setLocale(locale);

    _inputName->setLocale(locale);
    _inputName->setValidator(new QRegularExpressionValidator(nameRegExp, this));
    _inputWarranty->setValidator(new QIntValidator(1, std::numeric_limits<int>::max(), this));
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

    for (pqxx::row const &row : Component::getComponentTypes())
        _comboTypeName->addItem(QString::fromStdString(row[1].c_str()), QVariant(atoi(row[0].c_str())));
}

void AddComponentDialog::addComponent()
{
    if (_inputName->text().isEmpty() || _inputWarranty->text().isEmpty() || _inputPrice->text().isEmpty()) {
        //todo handle
        return;
    }

    DBComponent dbComponent(-1, _inputName->text().toStdString(), _comboTypeName->itemData(_comboTypeName->currentIndex()).toInt(), _comboTypeName->currentText().toStdString(), _inputWarranty->text().toInt(), _inputPrice->text().toFloat());

    Component::addComponent(dbComponent);
}

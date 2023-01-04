#include "adduserdialog.h"
#include "ui_adduserdialog.h"
#include "user.h"
#include "group.h"
#include "regularexpressions.h"

#include <pqxx/pqxx>
#include <QMessageBox>

AddUserDialog::AddUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUserDialog)
{
    ui->setupUi(this);

    setWindowTitle("Добавить пользователя");

    // Init pointers to UI elements
    _buttonAddUser = findChild<QPushButton*>("buttonAddUser");
    _comboGroupName = findChild<QComboBox*>("comboGroupName");
    _inputPassword = findChild<QLineEdit*>("inputPassword");

    // Validators
    _inputPassword->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));

    // Connections
    connect(_buttonAddUser, &QPushButton::clicked, this, &AddUserDialog::addUser);

    // Fill the QComboBox with component types
    loadGroups();
}

AddUserDialog::~AddUserDialog()
{
    delete ui;
}

void AddUserDialog::loadGroups()
{
    _comboGroupName->clear();

    for (const auto &row : Group::getGroups())
        _comboGroupName->addItem(row->name, QVariant(row->id));
}

void AddUserDialog::addUser()
{
    if (_inputPassword->text().isEmpty()) {
        QMessageBox::information(nullptr, "Предупреждение", "Заполните все поля!");
        return;
    }

    User::addUser(User::getEncryptedPassword(_inputPassword->text()), _comboGroupName->itemData(_comboGroupName->currentIndex()).toInt());

    close();
    deleteLater();

    QMessageBox::information(nullptr, "Информация", "Пользователь добавлен!");
}

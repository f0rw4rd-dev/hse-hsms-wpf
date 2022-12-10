#include "adduserdialog.h"
#include "ui_adduserdialog.h"
#include "user.h"

#include <pqxx/pqxx>

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

    for (pqxx::row const &row : User::getGroups())
        _comboGroupName->addItem(QString::fromStdString(row[1].c_str()), QVariant(atoi(row[0].c_str())));
}

void AddUserDialog::addUser()
{
    if (_inputPassword->text().isEmpty()) {
        //todo handle
        return;
    }

    User::addUser(User::getEncryptedPassword(_inputPassword->text()), _comboGroupName->itemData(_comboGroupName->currentIndex()).toInt());
}

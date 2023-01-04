#include "setuserdialog.h"
#include "ui_setuserdialog.h"
#include "group.h"
#include "user.h"
#include "regularexpressions.h"

#include <QPushButton>
#include <QMessageBox>

SetUserDialog::SetUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetUserDialog)
{
    ui->setupUi(this);

    setWindowTitle("Изменить пользователя");

    // Init pointers to UI elements
    _buttonSetUser = findChild<QPushButton*>("buttonSetUser");
    _comboGroupName = findChild<QComboBox*>("comboGroupName");
    _inputId = findChild<QLineEdit*>("inputId");
    _inputPassword = findChild<QLineEdit*>("inputPassword");

    _inputId->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputPassword->setValidator(new QRegularExpressionValidator(RegularExpressions::password, this));

    // Connections
    connect(_inputId, &QLineEdit::textChanged, this, &SetUserDialog::loadUser);
    connect(_buttonSetUser, &QPushButton::clicked, this, &SetUserDialog::setUser);

    loadGroups();
}

SetUserDialog::~SetUserDialog()
{
    delete ui;
}

void SetUserDialog::loadGroups()
{
    _comboGroupName->clear();

    for (const auto &row : Group::getGroups())
        _comboGroupName->addItem(row->name, QVariant(row->id));
}

void SetUserDialog::loadUser(const QString &id)
{
    QScopedPointer<DBUser> dbUser = User::getUser(id.toInt());

    if (dbUser == nullptr) {
        loadGroups();
        return;
    }

    _comboGroupName->setCurrentIndex(_comboGroupName->findData(QVariant(dbUser->group->id)));
}

void SetUserDialog::setUser()
{
    if (_inputId->text().isEmpty()) {
        QMessageBox::information(nullptr, "Предупреждение", "Заполните поле ИД!");
        return;
    }

    if (!User::doesUserExist(_inputId->text().toInt())) {
        QMessageBox::information(nullptr, "Предупреждение", "Данный пользователь не существует!");
        return;
    }

    User::setUserGroup(_inputId->text().toInt(), _comboGroupName->itemData(_comboGroupName->currentIndex()).toInt());

    if (!_inputPassword->text().isEmpty()) {
        User::setUserPassword(_inputId->text().toInt(), _inputPassword->text());
    }

    close();
    deleteLater();

    QMessageBox::information(nullptr, "Информация", "Информация о пользователе изменена!");
}


#include "deleteuserdialog.h"
#include "ui_deleteuserdialog.h"
#include "user.h"
#include "regularexpressions.h"

#include <QPushButton>
#include <QRegularExpressionValidator>
#include <QMessageBox>

DeleteUserDialog::DeleteUserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteUserDialog)
{
    ui->setupUi(this);

    setWindowTitle("Удалить пользователя");

    // Init pointers to UI elements
    _buttonDeleteUser = findChild<QPushButton*>("buttonDeleteUser");
    _inputId = findChild<QLineEdit*>("inputId");

    // Validators
    _inputId->setValidator(new QRegularExpressionValidator(RegularExpressions::integer, this));

    // Connections
    connect(_buttonDeleteUser, &QPushButton::clicked, this, &DeleteUserDialog::deleteUser);
}

DeleteUserDialog::~DeleteUserDialog()
{
    delete ui;
}

void DeleteUserDialog::deleteUser()
{
    if (_inputId->text().isEmpty()) {
        QMessageBox::information(nullptr, "Предупреждение", "Заполните все поля!");
        return;
    }

    if (!User::isUserExist(_inputId->text().toInt())) {
        QMessageBox::information(nullptr, "Предупреждение", "Данного пользователя не существует!");
        return;
    }

    User::deleteUser(_inputId->text().toInt());

    close();

    QMessageBox::information(nullptr, "Информация", "Пользователь удален!");
}

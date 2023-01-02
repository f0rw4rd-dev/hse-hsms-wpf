#include "deletecomponentdialog.h"
#include "ui_deletecomponentdialog.h"
#include "component.h"
#include "regularexpressions.h"

#include <QIntValidator>
#include <QMessageBox>

DeleteComponentDialog::DeleteComponentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteComponentDialog)
{
    ui->setupUi(this);

    setWindowTitle("Удалить комплектующее");

    // Init pointers to UI elements
    _buttonDeleteComponent = findChild<QPushButton*>("buttonDeleteComponent");
    _inputId = findChild<QLineEdit*>("inputId");

    // Validators
    _inputId->setValidator(new QRegularExpressionValidator(RegularExpressions::integer, this));

    // Connections
    connect(_buttonDeleteComponent, &QPushButton::clicked, this, &DeleteComponentDialog::deleteComponent);
}

DeleteComponentDialog::~DeleteComponentDialog()
{
    delete ui;
}

void DeleteComponentDialog::deleteComponent()
{
    if (_inputId->text().isEmpty()) {
        QMessageBox::information(nullptr, "Предупреждение", "Заполните все поля!");
        return;
    }

    if (!Component::doesComponentExist(_inputId->text().toInt())) {
        QMessageBox::information(nullptr, "Предупреждение", "Данного комплектующего нет!");
        return;
    }

    Component::deleteComponent(_inputId->text().toInt());

    close();

    QMessageBox::information(nullptr, "Информация", "Комплектующее удалено!");
}

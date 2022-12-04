#include "deletecomponentdialog.h"
#include "ui_deletecomponentdialog.h"
#include "component.h"

#include <QIntValidator>

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
    _inputId->setValidator(new QIntValidator(1, std::numeric_limits<int>::max(), this));

    // Connections
    connect(_buttonDeleteComponent, &QPushButton::clicked, this, &DeleteComponentDialog::deleteComponent);
}

DeleteComponentDialog::~DeleteComponentDialog()
{
    delete ui;
}

void DeleteComponentDialog::deleteComponent()
{
    Component::deleteComponent(_inputId->text().toInt());
}

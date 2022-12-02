#include "addcomponentdialog.h"
#include "ui_addcomponentdialog.h"

#include "component.h"

#include <QVariant>

AddComponentDialog::AddComponentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddComponentDialog)
{
    ui->setupUi(this);

    buttonBox = findChild<QDialogButtonBox*>("buttonBox");

    comboTypeName = findChild<QComboBox*>("comboTypeName");

    inputName = findChild<QLineEdit*>("inputName");
    inputWarranty = findChild<QLineEdit*>("inputWarranty");
    inputPrice = findChild<QLineEdit*>("inputPrice");

    loadComponentTypes();

    //todo validators

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(addComponent()));
}

AddComponentDialog::~AddComponentDialog()
{
    delete ui;
}

void AddComponentDialog::loadComponentTypes()
{
    comboTypeName->clear();

    for (pqxx::row const &row : Component::getComponentTypes())
        comboTypeName->addItem(QString::fromStdString(row[1].c_str()), QVariant(atoi(row[0].c_str())));
}

void AddComponentDialog::addComponent()
{
    if (inputName->text().isEmpty() || inputWarranty->text().isEmpty() || inputPrice->text().isEmpty()) {
        //todo handle
        return;
    }

    DBComponent dbComponent(-1, inputName->text().toStdString(), comboTypeName->itemData(comboTypeName->currentIndex()).toInt(), comboTypeName->currentText().toStdString(), inputWarranty->text().toInt(), inputPrice->text().toFloat());

    Component::addComponent(dbComponent);
}

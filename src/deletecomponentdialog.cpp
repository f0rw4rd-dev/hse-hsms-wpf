#include "deletecomponentdialog.h"
#include "ui_deletecomponentdialog.h"

DeleteComponentDialog::DeleteComponentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteComponentDialog)
{
    ui->setupUi(this);
}

DeleteComponentDialog::~DeleteComponentDialog()
{
    delete ui;
}

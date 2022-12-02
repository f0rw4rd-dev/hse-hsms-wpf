#include "editcomponentdialog.h"
#include "ui_editcomponentdialog.h"

EditComponentDialog::EditComponentDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditComponentDialog)
{
    ui->setupUi(this);
}

EditComponentDialog::~EditComponentDialog()
{
    delete ui;
}

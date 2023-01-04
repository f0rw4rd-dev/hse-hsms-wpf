#ifndef ADDWAREHOUSEDIALOG_H
#define ADDWAREHOUSEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>

namespace Ui {
class AddWarehouseDialog;
}

class AddWarehouseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddWarehouseDialog(QWidget *parent = nullptr);
    ~AddWarehouseDialog();

private slots:
    void addWarehouse();

private:
    QPushButton *_buttonAddWarehouse;
    QLineEdit *_inputCity;
    QLineEdit *_inputStreet;
    QLineEdit *_inputHouse;
    QLineEdit *_inputZip;

private:
    Ui::AddWarehouseDialog *ui;
};

#endif // ADDWAREHOUSEDIALOG_H

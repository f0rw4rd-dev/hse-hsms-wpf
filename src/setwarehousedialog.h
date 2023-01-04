#ifndef SETWAREHOUSEDIALOG_H
#define SETWAREHOUSEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>

namespace Ui {
class SetWarehouseDialog;
}

class SetWarehouseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetWarehouseDialog(QWidget *parent = nullptr);
    ~SetWarehouseDialog();

private slots:
    void loadWarehouse(const QString &id);
    void setWarehouse();

private:
    QPushButton *_buttonSetWarehouse;
    QLineEdit *_inputId;
    QLineEdit *_inputCity;
    QLineEdit *_inputStreet;
    QLineEdit *_inputHouse;
    QLineEdit *_inputZip;

private:
    Ui::SetWarehouseDialog *ui;
};

#endif // SETWAREHOUSEDIALOG_H

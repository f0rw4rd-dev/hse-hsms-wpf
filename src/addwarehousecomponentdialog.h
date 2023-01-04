#ifndef ADDWAREHOUSECOMPONENTDIALOG_H
#define ADDWAREHOUSECOMPONENTDIALOG_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class AddWarehouseComponentDialog;
}

class AddWarehouseComponentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddWarehouseComponentDialog(QWidget *parent = nullptr);
    ~AddWarehouseComponentDialog();

private slots:
    void addWarehouseComponent();

private:
    QPushButton *_buttonAddWarehouseComponent;
    QLineEdit *_inputComponentId;
    QLineEdit *_inputWarehouseId;
    QLineEdit *_inputAmount;

private:
    Ui::AddWarehouseComponentDialog *ui;
};

#endif // ADDWAREHOUSECOMPONENTDIALOG_H

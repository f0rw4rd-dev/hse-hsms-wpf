#ifndef DELETEWAREHOUSEDIALOG_H
#define DELETEWAREHOUSEDIALOG_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class DeleteWarehouseDialog;
}

class DeleteWarehouseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteWarehouseDialog(QWidget *parent = nullptr);
    ~DeleteWarehouseDialog();

private slots:
    void deleteWarehouse();

private:
    QPushButton *_buttonDeleteWarehouse;
    QLineEdit *_inputId;

private:
    Ui::DeleteWarehouseDialog *ui;
};

#endif // DELETEWAREHOUSEDIALOG_H

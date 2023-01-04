#ifndef DELETEWAREHOUSECOMPONENTDIALOG_H
#define DELETEWAREHOUSECOMPONENTDIALOG_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class DeleteWarehouseComponentDialog;
}

class DeleteWarehouseComponentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteWarehouseComponentDialog(QWidget *parent = nullptr);
    ~DeleteWarehouseComponentDialog();

private slots:
    void deleteWarehouseComponent();

private:
    QPushButton *_buttonDeleteWarehouseComponent;
    QLineEdit *_inputComponentId;
    QLineEdit *_inputWarehouseId;

private:
    Ui::DeleteWarehouseComponentDialog *ui;
};

#endif // DELETEWAREHOUSECOMPONENTDIALOG_H

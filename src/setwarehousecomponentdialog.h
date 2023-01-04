#ifndef SETWAREHOUSECOMPONENTDIALOG_H
#define SETWAREHOUSECOMPONENTDIALOG_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class SetWarehouseComponentDialog;
}

class SetWarehouseComponentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetWarehouseComponentDialog(QWidget *parent = nullptr);
    ~SetWarehouseComponentDialog();

private slots:
    void loadWarehouseComponent(const QString &id);
    void setWarehouseComponent();

private:
    QPushButton *_buttonSetWarehouseComponent;
    QLineEdit *_inputComponentId;
    QLineEdit *_inputWarehouseId;
    QLineEdit *_inputAmount;

private:
    Ui::SetWarehouseComponentDialog *ui;
};

#endif // SETWAREHOUSECOMPONENTDIALOG_H

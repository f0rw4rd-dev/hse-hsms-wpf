#ifndef SETCOMPONENTDIALOG_H
#define SETCOMPONENTDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>

namespace Ui {
class SetComponentDialog;
}

class SetComponentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetComponentDialog(QWidget *parent = nullptr);
    ~SetComponentDialog();

private:
    void loadComponentTypes();

private slots:
    void loadComponent(const QString &id);
    void setComponent();

private:
    QPushButton *_buttonSetComponent;
    QComboBox *_comboTypeName;
    QLineEdit *_inputId;
    QLineEdit *_inputName;
    QLineEdit *_inputWarranty;
    QLineEdit *_inputPrice;

private:
    Ui::SetComponentDialog *ui;
};

#endif // SETCOMPONENTDIALOG_H

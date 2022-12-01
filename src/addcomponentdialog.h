#ifndef ADDCOMPONENTDIALOG_H
#define ADDCOMPONENTDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QDialogButtonBox>

namespace Ui {
class AddComponentDialog;
}

class AddComponentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddComponentDialog(QWidget *parent = nullptr);
    ~AddComponentDialog();

private:
    void loadComponentTypes();

private slots:
    void addComponent();

private:
    QDialogButtonBox *buttonBox;

    QComboBox *comboTypeName;

    QLineEdit *inputName;
    QLineEdit *inputWarranty;
    QLineEdit *inputPrice;

private:
    Ui::AddComponentDialog *ui;
};

#endif // ADDCOMPONENTDIALOG_H

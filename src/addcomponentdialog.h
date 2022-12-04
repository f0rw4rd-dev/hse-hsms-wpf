#ifndef ADDCOMPONENTDIALOG_H
#define ADDCOMPONENTDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>

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
    QPushButton *_buttonAddComponent;
    QComboBox *_comboTypeName;
    QLineEdit *_inputName;
    QLineEdit *_inputWarranty;
    QLineEdit *_inputPrice;

private:
    Ui::AddComponentDialog *ui;
};

#endif // ADDCOMPONENTDIALOG_H

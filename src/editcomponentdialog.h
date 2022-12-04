#ifndef EDITCOMPONENTDIALOG_H
#define EDITCOMPONENTDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>

namespace Ui {
class EditComponentDialog;
}

class EditComponentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditComponentDialog(QWidget *parent = nullptr);
    ~EditComponentDialog();

private:
    void loadComponentTypes();

private slots:
    void loadComponent(const QString &id);
    void editComponent();

private:
    QPushButton *_buttonEditComponent;
    QComboBox *_comboTypeName;
    QLineEdit *_inputId;
    QLineEdit *_inputName;
    QLineEdit *_inputWarranty;
    QLineEdit *_inputPrice;

private:
    Ui::EditComponentDialog *ui;
};

#endif // EDITCOMPONENTDIALOG_H

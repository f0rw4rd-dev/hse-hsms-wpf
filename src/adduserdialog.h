#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>

namespace Ui {
class AddUserDialog;
}

class AddUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddUserDialog(QWidget *parent = nullptr);
    ~AddUserDialog();

private:
    void loadGroups();

private slots:
    void addUser();

private:
    QPushButton *_buttonAddUser;
    QComboBox *_comboGroupName;
    QLineEdit *_inputPassword;

private:
    Ui::AddUserDialog *ui;
};

#endif // ADDUSERDIALOG_H

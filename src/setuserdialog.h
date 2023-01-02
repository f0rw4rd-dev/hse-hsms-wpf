#ifndef SETUSERDIALOG_H
#define SETUSERDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>

namespace Ui {
class SetUserDialog;
}

class SetUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetUserDialog(QWidget *parent = nullptr);
    ~SetUserDialog();

private:
    void loadGroups();

private slots:
    void loadUser(const QString &id);
    void setUser();

private:
    QPushButton *_buttonSetUser;
    QComboBox *_comboGroupName;
    QLineEdit *_inputId;
    QLineEdit *_inputPassword;

private:
    Ui::SetUserDialog *ui;
};

#endif // SETUSERDIALOG_H

#ifndef DELETEUSERDIALOG_H
#define DELETEUSERDIALOG_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class DeleteUserDialog;
}

class DeleteUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteUserDialog(QWidget *parent = nullptr);
    ~DeleteUserDialog();

private slots:
    void deleteUser();

private:
    QPushButton *_buttonDeleteUser;
    QLineEdit *_inputId;

private:
    Ui::DeleteUserDialog *ui;
};

#endif // DELETEUSERDIALOG_H

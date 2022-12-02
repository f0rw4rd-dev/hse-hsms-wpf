#ifndef DELETECOMPONENTDIALOG_H
#define DELETECOMPONENTDIALOG_H

#include <QDialog>

namespace Ui {
class DeleteComponentDialog;
}

class DeleteComponentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteComponentDialog(QWidget *parent = nullptr);
    ~DeleteComponentDialog();

private:
    Ui::DeleteComponentDialog *ui;
};

#endif // DELETECOMPONENTDIALOG_H

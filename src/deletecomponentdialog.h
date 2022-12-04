#ifndef DELETECOMPONENTDIALOG_H
#define DELETECOMPONENTDIALOG_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class DeleteComponentDialog;
}

class DeleteComponentDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteComponentDialog(QWidget *parent = nullptr);
    ~DeleteComponentDialog();

private slots:
    void deleteComponent();

private:
    QPushButton *_buttonDeleteComponent;
    QLineEdit *_inputId;

private:
    Ui::DeleteComponentDialog *ui;
};

#endif // DELETECOMPONENTDIALOG_H

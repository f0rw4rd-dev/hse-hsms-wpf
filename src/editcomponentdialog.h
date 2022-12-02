#ifndef EDITCOMPONENTDIALOG_H
#define EDITCOMPONENTDIALOG_H

#include <QDialog>

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
    Ui::EditComponentDialog *ui;
};

#endif // EDITCOMPONENTDIALOG_H

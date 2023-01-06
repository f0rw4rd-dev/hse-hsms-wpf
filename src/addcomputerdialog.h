#ifndef ADDCOMPUTERDIALOG_H
#define ADDCOMPUTERDIALOG_H

#include <QDialog>
#include <QLineEdit>

namespace Ui {
class AddComputerDialog;
}

class AddComputerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddComputerDialog(QWidget *parent = nullptr);
    ~AddComputerDialog();

private slots:
    void loadCpu(const QString &id);
    void addComputer();

private:
    QPushButton *_buttonAddComputer;

    QLineEdit *_inputCPUId;
    QLineEdit *_inputCPUName;

    QLineEdit *_inputMotherboardId;
    QLineEdit *_inputMotherboardName;

    QLineEdit *_inputVideocardId;
    QLineEdit *_inputVideocardName;

    QLineEdit *_inputRAMId;
    QLineEdit *_inputRAMName;
    QLineEdit *_inputRAMAmount;

    QLineEdit *_inputCaseId;
    QLineEdit *_inputCaseName;

    QLineEdit *_inputPSUId;
    QLineEdit *_inputPSUName;

    QLineEdit *_inputHDDId;
    QLineEdit *_inputHDDName;
    QLineEdit *_inputHDDAmount;

    QLineEdit *_inputSSDId;
    QLineEdit *_inputSSDName;
    QLineEdit *_inputSSDAmount;

    QLineEdit *_inputSSDM2Id;
    QLineEdit *_inputSSDM2Name;
    QLineEdit *_inputSSDM2Amount;

    QLineEdit *_inputFanId;
    QLineEdit *_inputFanName;
    QLineEdit *_inputFanAmount;

    QLineEdit *_inputWCSId;
    QLineEdit *_inputWCSName;

    QLineEdit *_inputCoolerId;
    QLineEdit *_inputCoolerName;

private:
    Ui::AddComputerDialog *ui;
};

#endif // ADDCOMPUTERDIALOG_H

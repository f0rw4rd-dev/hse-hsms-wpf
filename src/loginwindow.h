#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void authorize();

private:
    QLineEdit *_inputLogin;
    QLineEdit *_inputPassword;

    QPushButton *_buttonLogin;

private:
    Ui::LoginWindow *ui;
};

#endif // LOGINWINDOW_H

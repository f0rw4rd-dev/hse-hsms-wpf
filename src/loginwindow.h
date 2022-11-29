#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>

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
    Ui::LoginWindow *ui;

    QLineEdit *inputLogin;
    QLineEdit *inputPassword;
};

#endif // LOGINWINDOW_H

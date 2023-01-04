#include "loginwindow.h"
#include "ui_loginwindow.h"

#include "user.h"

#include "regularexpressions.h"

#include <QIntValidator>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QStackedWidget>

#include <pqxx/pqxx>
#include <QMessageBox>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    // Adjust LoginWindow
    setFixedSize(QSize(1000, 600));

    // Init pointers to UI elements
    _inputLogin = findChild<QLineEdit*>("inputLogin");
    _inputPassword = findChild<QLineEdit*>("inputPassword");
    _buttonLogin = findChild<QPushButton*>("buttonLogin");

    // Validators
    _inputLogin->setValidator(new QRegularExpressionValidator(RegularExpressions::digit, this));
    _inputPassword->setValidator(new QRegularExpressionValidator(RegularExpressions::password, this));

    // Connections
    connect(_buttonLogin, &QPushButton::clicked, this, &LoginWindow::authorize);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::authorize()
{
    QStackedWidget *stackedWidget = reinterpret_cast<QStackedWidget*>(parentWidget());

    if (_inputLogin->text().isEmpty() || _inputPassword->text().isEmpty()) {
        QMessageBox::information(nullptr, "Предупреждение", "Заполните все поля!");
        return;
    }

    if (!User::doesUserExist(_inputLogin->text().toInt())) {
        QMessageBox::information(nullptr, "Предупреждение", "Данного пользователя не существует!");
        return;
    }

    if (!User::areCredentialsCorrect(_inputLogin->text(), _inputPassword->text())) {
        QMessageBox::information(nullptr, "Предупреждение", "Неверные данные!");
        return;
    }

    User::updateLastVisitDate(_inputLogin->text());

    stackedWidget->setCurrentIndex(0);
}

#include "loginwindow.h"
#include "ui_loginwindow.h"

#include "user.h"

#include <QIntValidator>
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include <QStackedWidget>

#include <pqxx/pqxx>

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
    QRegularExpression passwordRegExp("[a-zA-Z0-9]+");
    _inputLogin->setValidator(new QIntValidator(0, std::numeric_limits<int>::max(), this));
    _inputPassword->setValidator(new QRegularExpressionValidator(passwordRegExp, this));

    // Connectors
    connect(_buttonLogin, SIGNAL(clicked()), this, SLOT(authorize()));
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::authorize()
{
    QStackedWidget *stackedWidget = reinterpret_cast<QStackedWidget*>(parentWidget());

    if (_inputLogin->text().isEmpty() || _inputPassword->text().isEmpty()) {
        //todo handle
        return;
    }

    if (!User::isUserExist(_inputLogin->text())) {
        //todo handle
        return;
    }

    if (!User::areCredentialsCorrect(_inputLogin->text(), _inputPassword->text())) {
        //todo handle
        return;
    }

    User::updateLastVisitDate(_inputLogin->text());

    stackedWidget->setCurrentIndex(0);
}

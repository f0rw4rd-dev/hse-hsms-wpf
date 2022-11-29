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

    setFixedSize(QSize(1000, 600));

    inputLogin = findChild<QLineEdit*>("inputLogin");
    inputPassword = findChild<QLineEdit*>("inputPassword");

    inputLogin->setValidator(new QIntValidator(0, std::numeric_limits<int>::max(), this));

    QRegularExpression passwordRegExp("[a-zA-Z0-9]+");
    inputPassword->setValidator(new QRegularExpressionValidator(passwordRegExp, this));

    QPushButton *pbLogin = findChild<QPushButton*>("pbLogin");
    connect(pbLogin, SIGNAL(clicked()), this, SLOT(authorize()));
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::authorize()
{
    QStackedWidget *stackedWidget = reinterpret_cast<QStackedWidget*>(parentWidget());

    if (inputLogin->text().isEmpty() || inputPassword->text().isEmpty()) {
        //todo handle
        return;
    }

    if (!User::isUserExist(inputLogin->text())) {
        //todo handle
        return;
    }

    if (!User::areCredentialsCorrect(inputLogin->text(), inputPassword->text())) {
        //todo handle
        return;
    }

    User::updateLastVisitDate(inputLogin->text());

    stackedWidget->setCurrentIndex(1);
}

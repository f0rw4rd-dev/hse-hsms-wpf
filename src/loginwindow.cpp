#include "loginwindow.h"
#include "ui_loginwindow.h"

#include <iostream>
#include <pqxx/pqxx>

LoginWindow::LoginWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);

    QPushButton *pbLogin = findChild<QPushButton*>("pbLogin");
    connect(pbLogin, SIGNAL(clicked()), this, SLOT(authorize()));
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::authorize()
{
    QLineEdit *leLogin = findChild<QLineEdit*>("leLogin");
    QLineEdit *lePassword = findChild<QLineEdit*>("lePassword");

    try
    {
        // Connect to the database.  You can have multiple connections open
        pqxx::connection c("user=admin hostaddr=185.251.91.109 port=5432 password=b5gXN6NNeS2JO8Ug dbname=hardware_store");
        std::cout << "Connected to " << c.dbname() << '\n';

        pqxx::work tx{ c };

        int counter = 0;

        QString request = QString("SELECT id, password FROM users WHERE id = '%1' AND password = '%2';").arg(leLogin->text()).arg(lePassword->text());
        for (auto [id, password] : tx.query<int, std::string>(request.toStdString()))
            counter++;

        if (counter == 1)
            std::cout << "Fine!\n";
        else
            std::cout << "Bad!\n";

        //std::cout << "OK.\n";
    }
    catch (std::exception const& e)
    {
        std::cerr << "ERROR: " << e.what() << '\n';
        //return 1;
    }
}

#include "mainwindow.h"
#include "loginwindow.h"

#include <QApplication>

#include <iostream>
#include <pqxx/pqxx>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    LoginWindow w;
    w.show();

    try
    {
        // Connect to the database.  You can have multiple connections open
        pqxx::connection c("user=admin hostaddr=185.251.91.109 port=5432 password=b5gXN6NNeS2JO8Ug dbname=hardware_store");
        std::cout << "Connected to " << c.dbname() << '\n';

        pqxx::work tx{ c };

        // Query data of two columns, converting them to std::string and
        // int respectively.  Iterate the rows.
        for (auto [name, price] : tx.query<std::string, float>(
            "SELECT name, price FROM components ORDER BY price"))
        {
            std::cout << name << " | " << price << ".\n";
        }

        std::cout << "OK.\n";
    }
    catch (std::exception const& e)
    {
        std::cerr << "ERROR: " << e.what() << '\n';
        return 1;
    }

    return a.exec();
}

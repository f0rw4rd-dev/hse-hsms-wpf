#include "mainwindow.h"
#include "dbconnection.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    dbConnection = new DBConnection("admin", "b5gXN6NNeS2JO8Ug", "185.251.91.109", "5432", "hardware_store");

    if (!dbConnection->isConnectionReliable())
        return 0;

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}

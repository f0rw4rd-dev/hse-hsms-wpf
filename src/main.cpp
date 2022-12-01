#include "dbconnection.h"
#include "mainwindow.h"

#include <QApplication>
#include <QErrorMessage>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    dbConnection = new DBConnection("admin", "b5gXN6NNeS2JO8Ug", "185.251.91.109", "5432", "hardware_store");

    if (!dbConnection->isConnectionReliable()) {
        QMessageBox::critical(nullptr, "Ошибка", "Не удалось получить доступ к базе данных!");
        return 0;
    }

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}

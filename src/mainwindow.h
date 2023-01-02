#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Actions with components
    void loadComponents();
    void addComponent();
    void setComponent();
    void deleteComponent();

    // Actions with users
    void loadUsers();
    void addUser();
    void setUser();
    void deleteUser();

    // Actions with warehouses
    void loadWarehouses();
    void addWarehouse();

    // Actions with computers
    void loadComputers();
    void addComputer();

    // Actions with characteristics
    void loadCharacteristics();

    // Actions with components in warehouses
    void loadComponentsInWarehouses();

private:
    // UI elements for components
    QTableWidget *_tableComponents;
    QPushButton *_buttonLoadComponents;
    QPushButton *_buttonAddComponent;
    QPushButton *_buttonSetComponent;
    QPushButton *_buttonDeleteComponent;

    QTableWidget *_tableUsers;
    QPushButton *_buttonLoadUsers;
    QPushButton *_buttonAddUser;
    QPushButton *_buttonSetUser;
    QPushButton *_buttonDeleteUser;

    QTableWidget *_tableWarehouses;
    QPushButton *_buttonLoadWarehouses;
    QPushButton *_buttonAddWarehouse;

    QTableWidget *_tableComputers;
    QPushButton *_buttonLoadComputers;

    QTableWidget *_tableCharacteristics;
    QPushButton *_buttonLoadCharacteristics;

    QTableWidget *_tableComponentsInWarehouses;
    QPushButton *_buttonLoadComponentsInWarehouses;

    QStackedWidget *_stackedWidget;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

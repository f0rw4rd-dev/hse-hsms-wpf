#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QStackedWidget>

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
    void editComponent();
    void deleteComponent();

private:
    // Buttons for actions with components
    QPushButton *_buttonLoadComponents;
    QPushButton *_buttonAddComponent;
    QPushButton *_buttonEditComponent;
    QPushButton *_buttonDeleteComponent;

    QStackedWidget *_stackedWidget;

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

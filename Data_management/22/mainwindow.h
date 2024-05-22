#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// #include "shop.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void closeEvent(QCloseEvent*);

private slots:
    void on_PB_shop_clicked();

    void on_PB_salesman_clicked();

private:
    Ui::MainWindow *ui;

    class Shop* shop;
    class Salesman* salesman;
};
#endif // MAINWINDOW_H

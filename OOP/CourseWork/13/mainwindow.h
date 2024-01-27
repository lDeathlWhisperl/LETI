#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <deque>

class Car;
class Cashier;
class Petrolpump;

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
    void on_LE_petrol_pump_editingFinished();
    void on_LE_max_queue_editingFinished();

    void on_PBtn_set_clicked();
    void on_PBtn_reset_clicked();
    void on_PBtn_add_car_clicked();
    void on_PBtn_refuel_clicked();
    void on_Pbtn_serve_clicked();
    void on_PBtn_refuel_all_clicked();
    void on_PBtn_serve_all_clicked();

private:
    void updateInfoData();

private:
    Ui::MainWindow *ui;

    Cashier* cashier;
    std::deque<Car*> car;
    std::deque<Car*> cashier_queue;
    std::deque<Petrolpump*> pump;

    int pump_count = 0;
    int total_full_pumps = 0;
};
#endif // MAINWINDOW_H

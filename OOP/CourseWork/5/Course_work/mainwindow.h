#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include "workdone.h"

using std::vector;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Vehicle;
class Mechanic;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_LE_total_editingFinished();
    void on_LE_truck_editingFinished();
    void on_LE_mechanics_editingFinished();
    void on_LE_L_param_editingFinished();
    void on_PBtn_record_clicked();
    void on_PBtn_work_clicked();
    void on_PBtn_repeat_clicked();
    void on_PBtn_reset_clicked();

private:
    Ui::MainWindow *ui;

    int L_param = 1;
    vector<Vehicle*> car_queue;
    vector<Mechanic*> mech_queue;

    WorkDone form;

private:
    void onVehicleCountUpdate();
    void onMechanicCountUpdate();
    void updateVehicleInfo();
    void updateMechanicInfo();
};
#endif // MAINWINDOW_H

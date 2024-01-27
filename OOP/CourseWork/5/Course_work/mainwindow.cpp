#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "passenger.h"
#include "truck.h"
#include "passengermechanic.h"
#include "truckmechanic.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateVehicleInfo()
{
    car_queue.clear();

    for(int i = 0; i < Vehicle::passenger_count; ++i)
        car_queue.push_back(new Passenger());

    for(int i = 0; i < Vehicle::truck_count; ++i)
        car_queue.push_back(new Truck());
}

void MainWindow::updateMechanicInfo()
{
    mech_queue.clear();

    for(int i = 0; i < Mechanic::pass; ++i)
        mech_queue.push_back(new PassengerMechanic());

    for(int i = 0; i < Mechanic::veh; ++i)
        mech_queue.push_back(new TruckMechanic());
}

void MainWindow::on_LE_total_editingFinished()
{
    Vehicle::total = ui->LE_total->text().toInt();
    onVehicleCountUpdate();
}


void MainWindow::on_LE_truck_editingFinished()
{
    Vehicle::truck_count = ui->LE_truck->text().toInt();
    onVehicleCountUpdate();
}

void MainWindow::onVehicleCountUpdate()
{
    if(Vehicle::total < 0)
    {
        Vehicle::total = 0;
        ui->LE_total->setText(QString().number(0));
    }
    if(Vehicle::truck_count < 0)
    {
        Vehicle::truck_count = 0;
        ui->LE_truck->setText(QString().number(0));
    }
    if(Vehicle::truck_count > Vehicle::total)
    {
        Vehicle::truck_count = Vehicle::total;
        ui->LE_truck->setText(QString().number(Vehicle::truck_count));
    }

    Vehicle::passenger_count = Vehicle::total - Vehicle::truck_count;
    ui->L_pass->setText(QString().number(Vehicle::passenger_count));
}

void MainWindow::on_LE_mechanics_editingFinished()
{
    Mechanic::total = ui->LE_mechanics->text().toInt();
    onMechanicCountUpdate();
}


void MainWindow::on_LE_L_param_editingFinished()
{
    L_param = ui->LE_L_param->text().toInt();
    onMechanicCountUpdate();
}

void MainWindow::onMechanicCountUpdate()
{
    if(Mechanic::total < 0)
    {
        Mechanic::total = 0;
        ui->LE_mechanics->setText(QString().number(0));
    }
    if(L_param < 1)
    {
        L_param = 1;
        ui->LE_L_param->setText(QString().number(L_param));
    }

    Mechanic::pass = Mechanic::total / L_param;
    Mechanic::veh = Mechanic::total - Mechanic::pass;

    ui->L_mech_pass->setText(QString().number(Mechanic::pass));
    ui->L_mech_vehicle->setText(QString().number(Mechanic::veh));

    Mechanic::free_pass = Mechanic::pass;
    Mechanic::free_truck = Mechanic::veh;
}

void MainWindow::on_PBtn_record_clicked()
{
    ui->LE_L_param->setEnabled(false);
    ui->LE_mechanics->setEnabled(false);
    ui->LE_total->setEnabled(false);
    ui->LE_truck->setEnabled(false);
    ui->PBtn_repeat->setEnabled(true);
    ui->PBtn_work->setEnabled(true);

    ui->L_free_pass->setText(QString().number(Mechanic::free_pass));
    ui->L_free_truck->setText(QString().number(Mechanic::free_truck));

    ui->L_total_pass->setText(QString().number(Vehicle::passenger_count));
    ui->L_total_truck->setText(QString().number(Vehicle::truck_count));

    updateVehicleInfo();
    updateMechanicInfo();

    std::random_shuffle(car_queue.begin(), car_queue.end());
    std::random_shuffle(mech_queue.begin(), mech_queue.end());
}

void MainWindow::on_PBtn_repeat_clicked()
{
    ui->LE_L_param->setEnabled(true);
    ui->LE_mechanics->setEnabled(true);
    ui->LE_total->setEnabled(true);
    ui->LE_truck->setEnabled(true);
    ui->PBtn_repeat->setEnabled(false);
    ui->PBtn_work->setEnabled(false);

    Vehicle::total = -1;
    onVehicleCountUpdate();

    Mechanic::total = L_param = -1;
    onMechanicCountUpdate();

    ui->L_free_pass->setText(QString().number(Mechanic::free_pass));
    ui->L_free_truck->setText(QString().number(Mechanic::free_truck));

    ui->L_total_pass->setText(QString().number(Vehicle::passenger_count));
    ui->L_total_truck->setText(QString().number(Vehicle::truck_count));

    updateVehicleInfo();
    updateMechanicInfo();
}

void MainWindow::on_PBtn_work_clicked()
{
    if(mech_queue.empty() || car_queue.empty())
    {
        form.show();
        return;
    }

    mech_queue[0]->setBusy();
    for(int i = 0; i < car_queue.size(); ++i)
    {
        try
        {
            mech_queue[0]->repair(car_queue[i]);
            car_queue.erase(car_queue.begin() + i);
            break;
        }
        catch(WrongMechanicException)
        {
            continue;
        }
    }

    rest:
    //уход рабочего на перерыв
    mech_queue.push_back(mech_queue[0]);
    mech_queue.erase(mech_queue.begin());

    //если осталось меньше 25% свободных рабочих, то они по очереди выходят из отдыха
    int someindex = round(Mechanic::total * 0.25);
    mech_queue[someindex]->setFree();

    //window output:
    ui->L_free_pass->setText(QString().number(Mechanic::free_pass));
    ui->L_free_truck->setText(QString().number(Mechanic::free_truck));
    ui->L_total_pass->setText(QString().number(Vehicle::passenger_count));
    ui->L_total_truck->setText(QString().number(Vehicle::truck_count));
    ui->L_truck_repaired->setText(QString().number(Truck::repaired));
    ui->L_pass_repaired->setText(QString().number(Passenger::repaired));
}

void MainWindow::on_PBtn_reset_clicked()
{
    Truck::repaired = Passenger::repaired = 0;
    ui->L_truck_repaired->setText(QString().number(Truck::repaired));
    ui->L_pass_repaired->setText(QString().number(Passenger::repaired));
}


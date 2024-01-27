#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "car.h"
#include "cashier.h"
#include "petrolpump.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), cashier(new Cashier)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    car.clear();
    pump.clear();
    cashier_queue.clear();

    delete ui;
    delete cashier;
}

void MainWindow::updateInfoData()
{
    ui->L_car_queue->setText(QString().number(cashier_queue.size()));
    ui->L_total_car->setText(QString().number(car.size() + cashier_queue.size()));
    ui->L_car_served->setText(QString().number(Car::getServed()));
    ui->L_total_pump->setText(QString().number(pump.size()));
    ui->L_total_full->setText(QString().number(total_full_pumps));
}

void MainWindow::on_LE_petrol_pump_editingFinished()
{
    pump_count = ui->LE_petrol_pump->text().toInt();

    if(pump_count < 0)
    {
        pump_count = 0;
        ui->LE_petrol_pump->setText(QString().number(0));
    }
}

void MainWindow::on_LE_max_queue_editingFinished()
{
    Petrolpump::setMax_queue(ui->LE_max_queue->text().toInt());

    if(Petrolpump::getMax_queue() < 0)
    {
        Petrolpump::setMax_queue(0);
        ui->LE_max_queue->setText(QString().number(0));
    }
}

void MainWindow::on_PBtn_set_clicked()
{
    ui->PBtn_set->setEnabled(false);
    ui->LE_max_queue->setEnabled(false);
    ui->LE_petrol_pump->setEnabled(false);

    pump.clear();

    for(int i = 0; i < pump_count; ++i)
        pump.push_back(new Petrolpump());

    updateInfoData();
}

void MainWindow::on_PBtn_reset_clicked()
{
    ui->PBtn_set->setEnabled(true);
    ui->LE_max_queue->setEnabled(true);
    ui->LE_petrol_pump->setEnabled(true);
    ui->LE_max_queue->clear();
    ui->LE_petrol_pump->clear();

    car.clear();
    pump.clear();
    cashier_queue.clear();

    pump_count = 0;
    total_full_pumps = 0;

    Petrolpump::setMax_queue(0);
    Car::reset();

    updateInfoData();
}

void MainWindow::on_PBtn_add_car_clicked()
{
    if(Petrolpump::getMax_queue() * pump.size() == car.size()) return;

    car.push_back(new Car);

    pump[0]->setQueue();
    if(pump[0]->isFull()) ++total_full_pumps;

    pump.push_back(pump[0]);
    pump.pop_front();

    updateInfoData();
}

void MainWindow::on_PBtn_refuel_clicked()
{
    if(car.empty()) return;

    int last = pump.size() - 1;
    if(pump[last]->isFull()) --total_full_pumps;

    pump[last]->refuel(car[0]);
    cashier_queue.push_back(car[0]);
    car.pop_front();

    pump.push_front(pump[last]);
    pump.pop_back();

    updateInfoData();
}

void MainWindow::on_Pbtn_serve_clicked()
{
    if(cashier_queue.empty()) return;

    cashier->serve(cashier_queue[0]);
    cashier_queue.erase(cashier_queue.begin());

    updateInfoData();
}

void MainWindow::on_PBtn_refuel_all_clicked()
{
    if(car.empty()) return;

    while(!car.empty())
    {
        int last = pump.size() - 1;
        if(pump[last]->isFull()) --total_full_pumps;

        pump[last]->refuel(car[0]);
        cashier_queue.push_back(car[0]);
        car.pop_front();

        pump.push_front(pump[last]);
        pump.pop_back();
    }
    updateInfoData();
}

void MainWindow::on_PBtn_serve_all_clicked()
{
    if(cashier_queue.empty()) return;

    while(!cashier_queue.empty())
    {
        cashier->serve(cashier_queue[0]);
        cashier_queue.erase(cashier_queue.begin());
    }
    updateInfoData();
}


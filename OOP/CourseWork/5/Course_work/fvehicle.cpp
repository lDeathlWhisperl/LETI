#include "fvehicle.h"
#include "ui_fvehicle.h"

#include <QDebug>

FVehicle::FVehicle(QWidget *parent) :
    QWidget(parent), ui(new Ui::FVehicle)
{
    ui->setupUi(this);
}

FVehicle::~FVehicle()
{
    delete ui;
}

void FVehicle::on_LE_total_editingFinished()
{
    Vehicle::total = ui->LE_total->text().toInt();
    onVehicleCountChanged();
}

void FVehicle::on_LE_truck_editingFinished()
{
    Vehicle::truck_count = ui->LE_truck->text().toInt();
    onVehicleCountChanged();
}

void FVehicle::onVehicleCountChanged()
{
    if(Vehicle::total < 0)
    {
        Vehicle::total = 0;
        ui->LE_total->setText(QString::number(0));
    }

    if(Vehicle::truck_count < 0)
    {
        Vehicle::truck_count = 0;
        ui->LE_truck->setText(QString::number(0));
    }

    if(Vehicle::truck_count > Vehicle::total)
    {
        Vehicle::truck_count = Vehicle::total;
        ui->LE_truck->setText(QString::number(Vehicle::truck_count));
    }

    Vehicle::passenger_count = Vehicle::total - Vehicle::truck_count;
    ui->L_pass->setText(QString::number(Vehicle::passenger_count));
}

void FVehicle::closeEvent(QCloseEvent* event)
{
    qInfo() << "closed\n";
}

#ifndef FVEHICLE_H
#define FVEHICLE_H

#include <QWidget>
#include "passenger.h"
#include "truck.h"

namespace Ui {
class FVehicle;
}

class FVehicle : public QWidget
{
    Q_OBJECT

public:
    explicit FVehicle(QWidget *parent = nullptr);
    ~FVehicle();

    void closeEvent(QCloseEvent* event);

private slots:

    void on_LE_total_editingFinished();

    void on_LE_truck_editingFinished();

private:
    Ui::FVehicle *ui;

private:
    void onVehicleCountChanged();
};

#endif // FVEHICLE_H

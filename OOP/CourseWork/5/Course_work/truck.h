#ifndef TRUCK_H
#define TRUCK_H

#include "vehicle.h"

class Truck : public Vehicle
{
public:
    static int repaired;

public:
    Truck() : Vehicle() {}

    void repair();
    QString typeinfo() override { return "Truck"; }
};

#endif // TRUCK_H

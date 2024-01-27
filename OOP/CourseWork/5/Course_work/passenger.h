#ifndef PASSENGER_H
#define PASSENGER_H

#include "vehicle.h"

class Passenger : public Vehicle
{
public:
    static int repaired;

public:
    Passenger() : Vehicle() {}

    void repair();
    QString typeinfo() override { return "Passenger"; }
};

#endif // PASSENGER_H

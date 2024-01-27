#ifndef VEHICLE_H
#define VEHICLE_H

#include <QString>

class Vehicle
{
public:
    static int total;
    static int truck_count;
    static int passenger_count;

public:
    Vehicle() {}

    virtual void repair() = 0;
    virtual QString typeinfo() = 0;
};

#endif // VEHICLE_H

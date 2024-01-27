#ifndef TRUCKMECHANIC_H
#define TRUCKMECHANIC_H

#include "mechanic.h"

class Vehicle;

class TruckMechanic : public Mechanic
{
public:
    TruckMechanic() {}

    QString typeinfo() { return "TM"; }

    void setBusy() override;
    void setFree() override;
    void repair(Vehicle*);
};

#endif // TRUCKMECHANIC_H

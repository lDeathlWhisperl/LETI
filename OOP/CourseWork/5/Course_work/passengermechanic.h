#ifndef PASSENGERMECHANIC_H
#define PASSENGERMECHANIC_H

#include "mechanic.h"

class Passenger;

class PassengerMechanic : public Mechanic
{
public:
    PassengerMechanic() {}

    QString typeinfo() { return "PM"; }

    void setBusy() override;
    void setFree() override;

    void repair(Vehicle*);
};

#endif // PASSENGERMECHANIC_H

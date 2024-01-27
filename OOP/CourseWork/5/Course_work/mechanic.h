#ifndef MECHANIC_H
#define MECHANIC_H

#include <QString>

class WrongMechanicException {};
class Vehicle;

class Mechanic
{
public:
    static int total;
    static int pass;
    static int veh;
    static int free_pass;
    static int free_truck;

protected:
    bool isBusy;

public:
    Mechanic() : isBusy(false) {}

    virtual void repair(Vehicle*) = 0;
    virtual QString typeinfo() = 0;

    bool IsBusy() const { return isBusy; }
    virtual void setBusy() { isBusy = true;  }
    virtual void setFree() { isBusy = false; }
};

#endif // MECHANIC_H

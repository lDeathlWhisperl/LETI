#include "truckmechanic.h"
#include "vehicle.h"

void TruckMechanic::repair(Vehicle* car)
{
    car->repair();
}

void TruckMechanic::setBusy()
{
    if(isBusy) return;

    Mechanic::setBusy();
    --Mechanic::free_truck;
}

void TruckMechanic::setFree()
{
    if(!isBusy) return;

    Mechanic::setFree();
    ++Mechanic::free_truck;
}

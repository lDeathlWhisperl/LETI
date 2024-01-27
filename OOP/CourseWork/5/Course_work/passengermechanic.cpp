#include "passengermechanic.h"
#include "passenger.h"

void PassengerMechanic::repair(Vehicle *car)
{
    if(car->typeinfo() != Passenger().typeinfo()) throw WrongMechanicException();

    car->repair();
}

void PassengerMechanic::setBusy()
{
    if(isBusy) return;

    Mechanic::setBusy();
    --Mechanic::free_pass;
}

void PassengerMechanic::setFree()
{
    if(!isBusy) return;

    Mechanic::setFree();
    ++Mechanic::free_pass;
}

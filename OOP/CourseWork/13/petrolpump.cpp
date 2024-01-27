#include "petrolpump.h"
#include "car.h"

int Petrolpump::max_queue;

void Petrolpump::refuel(Car* car)
{
    car->refuel();
    --queue;
}

void Petrolpump::setQueue()
{
    if(queue < max_queue)
        ++queue;
}

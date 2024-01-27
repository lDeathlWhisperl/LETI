#include "truck.h"

int Truck::repaired;

void Truck::repair()
{
    --Vehicle::truck_count;
    ++repaired;
}

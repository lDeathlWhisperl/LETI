#include "passenger.h"

int Passenger::repaired;

void Passenger::repair()
{
    --Vehicle::passenger_count;
    ++repaired;
}

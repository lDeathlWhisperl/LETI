#include "cashier.h"
#include "car.h"

void Cashier::serve(Car* car)
{
    car->serve();
}

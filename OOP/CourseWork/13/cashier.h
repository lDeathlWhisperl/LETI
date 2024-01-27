#ifndef CASHIER_H
#define CASHIER_H

class Car;

class Cashier
{
public:
    Cashier() {}

    void serve(Car *car);
};

#endif // CASHIER_H

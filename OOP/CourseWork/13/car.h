#ifndef CAR_H
#define CAR_H

class Car
{
    static int served;
public:
    Car() {}

    void refuel();

    static int getServed() { return served; }
    void serve() { ++served; }
    static void reset() { served = 0; }
};

#endif // CAR_H

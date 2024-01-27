#ifndef PETROLPUMP_H
#define PETROLPUMP_H

class Car;

class Petrolpump
{
    static int max_queue;
    int queue = 0;

public:
    Petrolpump() {}

    static int getMax_queue()         { return max_queue; }
    static void setMax_queue(int num) { max_queue = num;  }

    void setQueue();
    int getQueue()  { return queue; }

    void refuel(Car* car);

    bool isFull() const  { return queue == max_queue; }
};

#endif // PETROLPUMP_H

#ifndef POLYNOM_H
#define POLYNOM_H

#include "number.h"
#include <QString>

class Polynom
{
    number a, b, c;

public:
    Polynom() : a(0), b(0), c(0) {}
	Polynom(number A, number B, number C) : a(A), b(B), c(C) {}
	
    QString solve();
	number solve(number);
    friend QString& operator<<(QString&, Polynom&);

    number getA() const { return a; }
    number getB() const { return b; }
    number getC() const { return c; }

    void setA(number a) { this->a = a; }
    void setB(number b) { this->b = b; }
    void setC(number c) { this->c = c; }
};

#endif // POLYNOM_H

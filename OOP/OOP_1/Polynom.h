#include "number.h"
#include <iostream>

class Polynom
{
	number a, b, c;
	
public:
	Polynom() : a(0), b(0), c(0) {}
	Polynom(number A, number B, number C) : a(A), b(B), c(C) {}
	
	void solve();
	void set();
	number solve(number);
	friend std::ostream& operator<<(std::ostream&, Polynom&);
};

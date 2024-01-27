#include "Polynom.h"
#include <sstream>
#include <cmath>
#include <typeinfo>

void Polynom::solve()
{
	if(a == 0)
	{
		std::cout << "\x1b[44mEnter non-zero coefficient a\x1b[0m\n";
		return;
	}
	else if(b == 0)
	{
		std::cout << "\x1b[44mEnter non-zero coeficient b\x1b[0m\n";
		return;
	}
	
	number D = b * b - 4 * a * c;
	
	if(D < 0)
		std::cout << "\x1b[44mThere are no valid roots\x1b[0m\n";
	else if(D == 0)
		std::cout  << 
			"\x1b[44m"     << *this        << "\x1b[0m\n" << 
			"\x1b[44mD = " << D            << "\x1b[0m\n" << 
			"\x1b[44mx = " << -b / (2 * a) << "\x1b[0m\n";
	else if(D > 0)
		std::cout   <<
			"\x1b[44m"      << *this                    << "\x1b[0m\n" <<
			"\x1b[44mD  = " << D                        << "\x1b[0m\n" <<
			"\x1b[44mx₁ = " << (-b + sqrt(D)) / (2 * a) << "\x1b[0m\n" <<
			"\x1b[44mx₂ = " << (-b - sqrt(D)) / (2 * a) << "\x1b[0m\n";
}

void Polynom::set()
{
	std::cout << "\n\x1b[44ma: ";
	std::cin >> a;
	std::cout << "\x1b[0m";
	
	std::cout << "\x1b[44mb: ";
	std::cin >> b;
	std::cout << "\x1b[0m";
	
	std::cout << "\x1b[44mc: ";
	std::cin >> c;
	std::cout << "\x1b[0m";
}

number Polynom::solve(number x)
{
	return a * x * x + b * x + c;
}

std::string sign(number num)
{	
	auto abs { [](number num) {return num < 0 ? num * -1 : num;} };
	
	if(num == -1)
		return " - ";
	else if(num == 1)
		return " + ";
	
	std::stringstream ss;
	
	if(num < 0)
	{
		ss << " - " << abs(num);
		return ss.str();
	}
	ss << " + " << num;
	return ss.str();
}

std::ostream& operator<<(std::ostream& out, Polynom &p)
{
	auto abs { [](number num) {return num < 0 ? num * -1 : num;} };
	std::stringstream ss;
	ss << p.a;
	
	out << 
		((abs(p.a) == 1) ? (p.a < 0 ? "-" : "") : ss.str()) << "x²" << 
		sign(p.b) << "x";
	
	ss.str(std::string());
	ss << abs(p.c);
	
	out << ((p.c == 0) ? "" : ((p.c < 0) ? (" - " + ss.str()) : (" + " + ss.str()))) << " = 0";
	return out;
}

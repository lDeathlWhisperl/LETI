#include <iostream>

class TComplex
{
	double real;
	double imaginary;
public:
	TComplex() : real(0), imaginary(0) {}
	TComplex(int num) : real(num), imaginary(0) {}
	TComplex(double R, double I) : real(R), imaginary(I) {}
	
	friend std::ostream& operator<<(std::ostream&, TComplex);
	friend std::istream& operator>>(std::istream&, TComplex&);
	
	TComplex operator+(TComplex);
	
	TComplex operator-();
	TComplex operator-(TComplex);
	
	TComplex 		operator*(TComplex);
	TComplex 		operator*(int);
	friend TComplex operator*(int, TComplex);
	
	TComplex operator/(TComplex);
	
	bool operator==(TComplex);
	bool operator==(int);
	
	bool operator<(int);	
	bool operator>(int);
	
	double getRe() const { return real; }
	double getIm() const { return imaginary; }
	
	double length();
};

TComplex sqrt(TComplex);

#ifndef TCOMPLEX_H
#define TCOMPLEX_H

#include <QString>

class TComplex
{
	double real;
	double imaginary;
public:
	TComplex() : real(0), imaginary(0) {}
	TComplex(int num) : real(num), imaginary(0) {}
	TComplex(double R, double I) : real(R), imaginary(I) {}
	
    friend QString& operator<<(QString&, TComplex);
	
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

#endif // TCOMPLEX_H

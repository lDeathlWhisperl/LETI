#include "TComplex.h"
#include <complex>

TComplex sqrt(TComplex complex)
{
	std::complex<double> comp(complex.getRe(), complex.getIm());
	comp = sqrt(comp);
	return TComplex(comp.real(), comp.imag());
}

std::ostream& operator<<(std::ostream& out, TComplex complex)
{
	return out << '(' << complex.real << (complex.imaginary < 0 ? " - " : " + ") << (complex.imaginary < 0 ? complex.imaginary * -1 : complex.imaginary) << "i)";
}

std::istream& operator>>(std::istream& in, TComplex& complex)
{
	std::cout << "Real part: ";
	in >> complex.real;
	
	std::cout << "Imaginary part: ";
	in >> complex.imaginary;
	
	return in;
}

TComplex TComplex::operator+(TComplex complex)
{
	return TComplex(real + complex.real, imaginary + complex.imaginary);
}

TComplex TComplex::operator-(TComplex complex)
{
	return TComplex(real - complex.real, imaginary - complex.imaginary);
}

TComplex TComplex::operator-()
{
	return -1 * *this;
}

TComplex TComplex::operator*(TComplex complex)
{
	return TComplex(real * complex.real - imaginary * complex.imaginary, real * complex.imaginary + complex.real * imaginary);
}

TComplex TComplex::operator*(int lambda)
{
	return TComplex(real * lambda, imaginary * lambda);
}

TComplex operator*(int lambda, TComplex complex)
{
	return complex * lambda;
}

TComplex TComplex::operator/(TComplex complex)
{
	double res_R = (real * complex.real + imaginary * complex.imaginary) / (complex.real * complex.real + complex.imaginary * complex.imaginary);
	double res_I = (imaginary * complex.real - real * complex.imaginary) / (complex.real * complex.real + complex.imaginary * complex.imaginary);
	return TComplex(res_R, res_I);
}

bool TComplex::operator==(TComplex complex)
{
	return real == complex.real && imaginary == complex.imaginary;
}

bool TComplex::operator==(int lambda)
{
	return length() == lambda;
}

bool TComplex::operator<(int lambda)
{
	return length() < lambda;
}

bool TComplex::operator>(int lambda)
{
	return length() > lambda;
}

double TComplex::length()
{
	return sqrt(real * real + imaginary * imaginary);
}

#include "TComplex.h"
#include <complex>

TComplex sqrt(TComplex complex)
{
	std::complex<double> comp(complex.getRe(), complex.getIm());
	comp = sqrt(comp);
	return TComplex(comp.real(), comp.imag());
}

QString& operator<<(QString& out, TComplex complex)
{
    if(complex.real != 0 && complex.imaginary != 0)
    {
        out += "(";
        out += QString().setNum(complex.real);
        out += (complex.imaginary < 0 ? " - " : " + ");
        out += (complex.imaginary < 0 ? QString().setNum(complex.imaginary * -1) : QString().setNum(complex.imaginary));
        out += "i)";
    }
    else if(complex.real == 0 && complex.imaginary != 0)
    {
        out += QString().setNum(complex.imaginary);
        out += 'i';
    }
    else
        out += QString().setNum(complex.real);

    return out;
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

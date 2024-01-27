#include "Polynom.h"
#include <sstream>
#include <cmath>

QString Polynom::solve()
{
    if(a == 0)
    {
        QString str;

        number x = -c / b;
        str = "x = ";
        str << x;

        return str;
    }
    else if(b == 0)
    {
        QString str;
        number x;
        //ax² + c = 0
        //ax² = -c
        //x² = -c / a
        str =  "x₁ = ";
        x = sqrt(-c / a);
        str << x;

        str += "\nx₂ = ";
        x = -sqrt(-c / a);
        str << x;

        return str;
    }

	number D = b * b - 4 * a * c;
	
    if(D < 0)
        return "There are no valid roots\n";
    else if(D == 0)
    {
        QString str;

        str += "D = ";
        str << D;
        str += "\nx = ";
        str << -b / (2 * a);
        str += "\n";

        return str;
    }

    QString str;
    str += "D = ";
    str << D;
    str += "\nx₁ = ";
    str << ((-b + sqrt(D)) / (2 * a));
    str += "\nx₂ = ";
    str << ((-b - sqrt(D)) / (2 * a));
    str += "\n";

    return str;
}

number Polynom::solve(number x)
{
	return a * x * x + b * x + c;
}

QString sign(double num)
{
    auto abs { [](double num) {return num < 0 ? -num : num;} };
    QString str;

    if(num == -1)
        return " - ";
    else if(num == 1)
        return " + ";

    if(num < 0)
    {
        str += " - ";
        str += QString().setNum(abs(num));
        return str;
    }

    str += " + ";
    str += QString().setNum(num);
    return str;
}


QString& operator<<(QString& out, Polynom &p)
{
    auto abs { [](double num) {return num < 0 ? -num : num;} };
    QString temp;

    //A//
    temp << p.a;
    if(p.a.getIm() == 0)
        out += ((abs(p.a.getRe()) == 1) ? (p.a.getRe() < 0 ? "-" : "") : temp);
    else
        out += temp;

    out += "x²";

    //B//
    if(p.b.getIm() == 0)
        out += sign(p.b.getRe());
    else
    {
        out += " + ";
        out << p.b;
    }
    out += "x";

    //C//
    temp = "";
    if(p.c.getIm() == 0)
    {
        temp += QString().setNum(abs(p.c.getRe()));
        out += ((p.c.getRe() == 0) ? "" : ((p.c.getRe() < 0) ? (" - " + temp) : (" + " + temp)));
    }
    else
    {
        out += " + ";
        out << p.c;
    }

    out += " = 0";
	return out;
}

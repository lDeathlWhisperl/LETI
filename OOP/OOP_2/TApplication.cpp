#include "TApplication.h"
#include "Polynom.h"

TApplication::TApplication() : polynom(new Polynom()) {}

TApplication::~TApplication()
{
	delete polynom;
}

void TApplication::menu()
{
	std::cout <<
		"\n"
		"[0. exit                  ]\n"
		"[1. enter the coefficients]\n"
		"[2. solve the equation    ]\n"
		"[3. solve through x       ]\n"
		"[4. show the equation     ]\n"
		"\n> ";
	
	int choice{};
	std::cin >> choice;
	
	switch(choice)
	{
	case 0:
		isActive = false;
		break;
	case 1:
		polynom->set();
		break;
	case 2:
		polynom->solve();
		break;
	case 3:
	{
		number x;
		std::cout << "\x1b[44mx: ";
		std::cin >> x;
		
		std::cout << "\x1b[0m\x1b[44m" << polynom->solve(x) << "\x1b[0m";
	}
		break;
	case 4:
		std::cout << "\x1b[44m" << *polynom << "\x1b[0m\n";
		break;
	}
}

int TApplication::exec()
{
	while(isActive)
		menu();
	return 0;
}

#include "HUD.h"
#include "Settings.h"
#include <windows.h>

static void gotoPoint(int x, int y)
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = x;
	Position.Y = y;
	SetConsoleCursorPosition(hOut, Position);
}

void HUD::setLength(int l)
{
	length = l + 2;
	pos_x = Settings::sett_HUD_x;
	pos_y = Settings::sett_HUD_y;
}

void HUD::frame()
{
	for (int i = 0; i < length; i++)
		std::cout << (unsigned char)219;
}

void HUD::healthBar(Character* character)
{
	std::cout << (unsigned char)219;

	for (int i = 1; i < length - 1; i++)
		if (i <= character->getHP())
			std::cout << "\x1b[31m" << (unsigned char)219 << "\x1b[0m";
		else
			std::cout << ' ';

	std::cout << (unsigned char)219;
}

void HUD::armorBar(Character* character)
{
	std::cout << (unsigned char)219;

	for (int i = 1; i < length - 1; i++)
		if (i <= character->getArmor())
			std::cout << "\x1b[32m" << (unsigned char)219 << "\x1b[0m";
		else
			std::cout << (unsigned char)219;


	std::cout << (unsigned char)219;
}

int HUD::getLength()
{
	return length;
}

void HUD::addToViewport(Character* character)
{	
	gotoPoint(pos_x, pos_y);

	int y;

	for (y = pos_y; y <= pos_y + 4; y++)
	{
		for (int x = pos_x; x < length + pos_x; x++)
		{
			if (x == pos_x && (y == pos_y || y == pos_y + 3))
				frame();

			else if (x == pos_x && y == pos_y + 1)
				healthBar(character);

			else if (x == pos_x && y == pos_y + 2)
				armorBar(character);
		}
		gotoPoint(pos_x, y + 1);
	}
	length += pos_x;
}
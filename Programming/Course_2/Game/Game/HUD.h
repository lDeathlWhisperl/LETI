#pragma once

#include <iostream>

#include "Character.h"

class HUD final
{
	int length = 0, pos_x = 0, pos_y = 0;

	void frame();

	void healthBar(Character*);

	void armorBar(Character*);

public:
	void setLength(int);

	int getLength();

	void setX(int x)
	{
		pos_x = x;
	}

	void setY(int y)
	{
		pos_y = y;
	}

	int getWidth()
	{
		return pos_y + 4;
	}

	int getPos_x()
	{
		return pos_x;
	}

	int getPos_y()
	{
		return pos_y;
	}

	void addToViewport(Character*);
};
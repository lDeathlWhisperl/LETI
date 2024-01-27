#pragma once

#include "Player.h"
#include "AI.h"

#include <iostream>

class Sword final
{
	static char sword;

	static int pos_x, pos_y;

    enum buttons
    {
        ARROW_UP    = 72,
        ARROW_LEFT  = 75,
        ARROW_RIGHT = 77,
        ARROW_DOWN  = 80,
    };

	static Player *owner;

	static AI* target;
public:
	Sword(Player*);

	void attack(char);

	static void setTarget(AI*);

	void draw();

	static int getPos_x();

	static int getPos_y();
};
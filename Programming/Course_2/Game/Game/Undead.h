#pragma once

#include "AI.h"

class Undead : public AI
{
public:
	Undead() : AI() 
	{
		character = '1';
	}

	Undead(int hp, int arm, int str, char lvl) : AI(hp, arm, str) 
	{
		character = lvl;
	}

	~Undead() {}
};
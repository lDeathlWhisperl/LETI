#pragma once

#include "AI.h"

class Demon : public AI
{
public:
	Demon() : AI() {}

	Demon(int hp, int arm, int str, char lvl) : AI(hp, arm, str) 
	{
		character = lvl;
	}

	~Demon() {}
};
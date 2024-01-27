#pragma once

#include "AI.h"

class Spirit : public AI
{
public:
	Spirit() : AI() 
	{
		character = '1';
	}

	Spirit(int hp, int arm, int str, char lvl) : AI(hp, arm, str)
	{
		character = lvl;
	}

	~Spirit() {}
};
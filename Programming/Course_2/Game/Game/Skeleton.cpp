#include "Skeleton.h"
#include "Logging.h"

Skeleton::Skeleton() : Undead()
{
	debug::log->request("Created [BOT SKELETON]  id: " + std::to_string(id) + "\n\n");
}

void Skeleton::draw()
{
	std::cout << "\x1b[47m\x1b[30m" << character << "\x1b[0m";
}
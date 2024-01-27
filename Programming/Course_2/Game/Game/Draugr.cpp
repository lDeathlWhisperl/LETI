#include "Draugr.h"
#include "Logging.h"

Draugr::Draugr() : Undead(10, 5, 5, '3')
{
	debug::log->request("Created [BOT DRAUGR]    id: " + std::to_string(id) + "\n\n");
}

void Draugr::draw()
{
	std::cout << "\x1b[42m\x1b[30m" << character << "\x1b[0m";
}
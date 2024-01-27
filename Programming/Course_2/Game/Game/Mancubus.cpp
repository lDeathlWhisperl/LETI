#include "Mancubus.h"
#include "Logging.h"

Mancubus::Mancubus() : Demon(15, 10, 8, '3')
{
	debug::log->request("Created [BOT MANCUBUS]  id: " + std::to_string(id) + "\n\n");
}

void Mancubus::draw()
{
	std::cout << "\x1b[41m\x1b[30m" << character << "\x1b[0m";
}
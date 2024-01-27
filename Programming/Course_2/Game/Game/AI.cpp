#include "AI.h"
#include "Logging.h"

AStar::Generator AI::generator;
int AI::count = 0;

static std::vector<int> w;

static bool exception(int x, int y)
{
	for (int i = 0; i < w.size() - 1; i += 2)
		if (w[i] == x && w[i + 1] == y)
			return true;
	return false;
}

AI::~AI()
{
	if (count == 1)
		generator.clearCollisions();
	count--;
	debug::log->request("[BOT] " + std::to_string(id) + " destroyed\n\n");
}

void AI::controller(Player& player)
{
	bool FOV = pos_x - 10 <= player.getPos_x() && pos_x + 10 >= player.getPos_x() &&
		       pos_y - 5 <= player.getPos_y() && pos_y + 5 >= player.getPos_y();

	if (!cooldown && status && FOV)
	{
		if (!canAttack)
		{
			auto path = generator.findPath({ pos_x, pos_y }, { player.getPos_x(), player.getPos_y() });
			
			size_t i = path.size() - 2;
			if (i > 0 && i < path.size())
			{
				pos_x = path[i].x;
				pos_y = path[i].y;
				cooldown = true;
				return;
			}
			else
				canAttack = true;
		}
		else
		{
			player.getDamage(attack());
			canAttack = false; 
		}
	}
	cooldown = false;
}

void AI::collision(std::vector<int> walls, int width, int height)
{	
	w = walls;
	generator.setWorldSize({ width, height });
	for (int i = 0; i < walls.size() - 1; i += 2)
		generator.addCollision({ walls[i], walls[i + 1] });
}

bool AI::isTarget()
{
	if (!status) target = false;
	return target;
}

void AI::setTarget()
{
	target = true;
}

void AI::deleteTarget()
{
	target = false;
}

void AI::getDamage(Player& damager)
{
	Character::getDamage(damager.getStrength());

	switch (damager.draw())
	{
	case '^':
		if (!exception(pos_x, pos_y - 1))--pos_y;
		break;
	case '>':
		if (!exception(pos_x + 1, pos_y))++pos_x;
		break;
	case 'V':
		if (!exception(pos_x, pos_y + 1))++pos_y;
		break;
	case '<':
		if (!exception(pos_x - 1, pos_y))--pos_x;
	}
}
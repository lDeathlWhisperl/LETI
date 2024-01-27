#include "Render.h"
#include "Castle.h"
#include "Pyramid.h"
#include "Logging.h"
#include "Sword.h"

//32 - tree
//92 - field

//34 - deep water
//94 - bright water
//36 - river

//93 - sand
//90 - stone
//33 - chest

void gotoPoint(int x, int y)
{
	HANDLE hOut;
	COORD Position;

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	Position.X = x;
	Position.Y = y;
	SetConsoleCursorPosition(hOut, Position);
}

std::string Render::paint(double high)
{
	std::string res;
	res.clear();
	unsigned char tile = 219;

	if (high <= 0.2)
		res = "\x1b[34m";				//deep water
	else if (high > 0.2 && high <= 0.3)
		res = "\x1b[94m";				//bright water
	else if (high > 0.3 && high <= 0.34)
		res = "\x1b[93m";				//sand and dessert
	else if (high > 0.5 && high <= 0.545)
		res = "\x1b[36m";				//river
	else
		res = "\x1b[92m";               //field

	switch ((int)high)
	{
	case 2:
	case 9:
		res = "\x1b[32m";				//tree and cactus
		break;
	case 3:
		res = "\x1b[90m";				//stone and dungeon walls
		break;
	case 4:
	case 5:
	case 10:
		res = "\x1b[33m";				//castle door and pyramid brick
		break;
	case 6:
		res = "\x1b[30m";				//window, dungeon void and pyramid passage
		break;
	case 7:
		res = "\x1b[96m";				//dungeon floor
		break;
	case 8:
		res = "\x1b[93m";				//pyramid floor
		break;
	}

	res += tile;
	res += "\x1b[0m";
	return res;
}
 
void Render::draw_castle_dungeon(Dungeon& dungeon, Player& player)
{
	HUD hud, monster_hud;
	hud.setLength(player.getMaxHP());
	int player_coords = dungeon.getVertex(player.getPos_x(), player.getPos_y());
	AI* target = NULL;

	hud.addToViewport(&player);
	update();

	for (int y = 0; y < dungeon.getHeight(); y++)
	{
		for (int x = 0; x < dungeon.getWidth()-1; x++)
		{
			bool p_coords = (x == player.getPos_x() && y == player.getPos_y());
			bool hud_coords = (x + 1 <= hud.getPos_x() || x + 1 > hud.getLength()) || (y + 1 <= hud.getPos_y() || y + 1 > hud.getWidth());
			bool skip = false;

			for (AI* monster : dungeon.monsters)
				if (monster->getPos_x() == x && monster->getPos_y() == y)
				{
					monster->draw();
					skip = true;
					Sword::setTarget(monster);
					if (monster->isTarget()) target = monster;
					break;
				}

			if (player.drawSword(x, y))
				break;

			if (p_coords && hud_coords && !skip)
				std::cout << player.draw();
			else if (hud_coords && !skip)
				std::cout << paint(dungeon.getVertex(x, y));
			else
				gotoPoint(x + 1, y);			
		}
		std::cout << '\n';
	}
		
	if (target)
	{
		monster_hud.setLength(target->getMaxHP());
		monster_hud.setX(dungeon.getWidth() - target->getMaxHP() - 3);
		monster_hud.setY(dungeon.getHeight());
		monster_hud.addToViewport(target);
	}
	else
	{
		gotoPoint(0, dungeon.getHeight());
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < dungeon.getWidth() - 1; ++j)				
				std::cout << ' ';
			std::cout << '\n';
		}
	}

	if (player_coords == 5 && player.getLastPressedKey() == 32)
		dungeon.Exit();
}

void Render::draw_pyramid_dungeon(Dungeon& dungeon, Player& player)
{
	HUD hud, monster_hud;
	hud.setLength(player.getMaxHP());
	int player_coords = dungeon.getVertex(player.getPos_x(), player.getPos_y());
	AI* target = NULL;

	hud.addToViewport(&player);
	update();

	for (int y = 0; y < dungeon.getHeight(); y++)
	{
		for (int x = 0; x < dungeon.getWidth()-1; x++)
		{
			bool p_coords = (x == player.getPos_x() && y == player.getPos_y());
			bool hud_coords = (x + 1 <= hud.getPos_x() || x + 1 > hud.getLength()) || (y + 1 <= hud.getPos_y() || y + 1 > hud.getWidth());
			bool skip = false;

			for (AI* monster : dungeon.monsters)
				if (monster->getPos_x() == x && monster->getPos_y() == y)
				{
					monster->draw();
					skip = true;
					Sword::setTarget(monster);
					if (monster->isTarget()) target = monster;
					break;
				}

			if (player.drawSword(x, y))
				break;

			if (p_coords && hud_coords && !skip)
				std::cout << player.draw();
			else if (hud_coords && !skip)
				std::cout << ((dungeon.getVertex(x, y) == 6) ? paint(6) : paint(dungeon.getVertex(x, y) + 1));
			else if (!skip)
				gotoPoint(x + 1, y);
		}
		std::cout << '\n';
	}

	if (target)
	{
		monster_hud.setLength(target->getMaxHP());
		monster_hud.setX(dungeon.getWidth() - target->getMaxHP() - 3);
		monster_hud.setY(dungeon.getHeight());
		monster_hud.addToViewport(target);
	}
	else
	{
		gotoPoint(0, dungeon.getHeight());
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < dungeon.getWidth() - 1; ++j)
				std::cout << ' ';
			std::cout << '\n';
		}
	}

	if (player_coords == 5 && player.getLastPressedKey() == 32)
		dungeon.Exit();
}

void Render::draw_world(World &world, Player &player)
{
	HUD hud;
	hud.setLength(player.getMaxHP());
	bool do_once = true;
		
	hud.addToViewport(&player);
	update();

	for (int y = 1; y < world.getWidth(); y++)
	{
		for (int x = 1; x < world.getLength(); x++)
		{
			bool player_coords = x == world.getLength() / 2 && y == world.getWidth() / 2,
				 hud_coords = (x <= hud.getPos_x() || x > hud.getLength()) || (y <= hud.getPos_y() || y > hud.getWidth());

			if (player_coords && world.getMap(x, y) != 2)
				std::cout << player.draw();
			else if (hud_coords)
				std::cout << paint(world.getMap(x, y));
			else
				gotoPoint(x, y - 1);
		}
		std::cout << '\n';
	}

	int player_coords = static_cast<int>(world.getMap(world.getLength() / 2, world.getWidth() / 2));

	//damage from a cactus
	if (player_coords == 9)
		player.getDamage(1);

	//enter into the castle
	if (player.getLastPressedKey() == 32 && player_coords == 5)
	{
		system("cls");
		Castle::enter(player, world.getLength(), world.getWidth());
		system("cls");
		return;
	}

	//enter into the pyramid
	if (player.getLastPressedKey() == 32 && player_coords == 6)
	{
		system("cls");
		Pyramid::enter(player, world.getLength(), world.getWidth());
		system("cls");
		return;
	}

}

void Render::update()
{
	gotoPoint(0, 0);
}
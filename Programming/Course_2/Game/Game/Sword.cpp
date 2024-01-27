#include "Sword.h"

int Sword::pos_x = -1,
Sword::pos_y = -1;

char Sword::sword = '\0';

Player* Sword::owner;

AI* Sword::target;

void Sword::attack(char lastPressedKey)
{
	switch (lastPressedKey)
	{
	case ARROW_UP:
		pos_x = owner->getPos_x();
		pos_y = owner->getPos_y() - 1;
		sword = '|';
		break;
	case ARROW_DOWN:
		pos_x = owner->getPos_x();
		pos_y = owner->getPos_y() + 1;
		sword = '|';
		break;
	case ARROW_RIGHT:
		pos_x = owner->getPos_x() + 1;
		pos_y = owner->getPos_y();
		sword = '-';
		break;
	case ARROW_LEFT:
		pos_x = owner->getPos_x() - 1;
		pos_y = owner->getPos_y();
		sword = '-';
		break;
	} 

	if (target && target->isTarget() && target->getPos_x() == pos_x && target->getPos_y() == pos_y)
	{
		target->getDamage(*owner);
		if (!target->getStatus()) owner->addMoney(target->getMaxHP());
	}
}

void Sword::setTarget(AI* trgt)
{
	if ((trgt->getPos_x() <= owner->getPos_x() + 10 && trgt->getPos_x() >= owner->getPos_x() - 10) &&
		(trgt->getPos_y() <= owner->getPos_y() + 5 && trgt->getPos_y() >= owner->getPos_y() - 5))
	{
		target = trgt;
		trgt->setTarget();
	}
	else
		trgt->deleteTarget();
}

void Sword::draw()
{
	std::cout << sword;
	pos_x = -1;
	pos_y = -1;
	target = NULL;
}

int Sword::getPos_x()
{
	return pos_x;
}

int Sword::getPos_y()
{
	return pos_y;
}

Sword::Sword(Player* player)
{
	owner = player;
}
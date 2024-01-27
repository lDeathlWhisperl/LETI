#include "Player.h"
#include <conio.h>
#include "Logging.h"
#include "Level.h"
#include "Sword.h"
#include <windows.h>

bool exception(int num)
{
    switch (num)
    {
    case 6:
    case 3:
        return true;
    default:
        return false;
    }
}

static void gotoPoint(int x, int y)
{
    HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = x;
    Position.Y = y;
    SetConsoleCursorPosition(hOut, Position);
}

Player::Player()
{
    character = '^';
    debug::log->request("Creating the player\n\n");
}

Player::~Player()
{
    debug::log->request("Deleting the player\n\n");
}

void Player::controller(int top, int left, int right, int bottom)
{
    Sword sword(this);
    char ch = '\0';
    if (_kbhit())
        ch = _getch();

    switch (ch)
    {
    case w:
    case W:
        if (!exception(top))
            pos_y--;
        character = '^';
        break;
    case ARROW_UP:
        sword.attack(ch);
        character = '^';
        break;
    case a:
    case A:
        if (!exception(left))
            pos_x--;
        character = '<';
        break;
    case ARROW_LEFT:
        character = '<';
        sword.attack(ch);
        break;
    case s:
    case S:
        if (!exception(bottom))
            pos_y++;
        character = 'V';
        break;
    case ARROW_DOWN:
        character = 'V';
        sword.attack(ch);
        break;
    case d:
    case D:
        if (!exception(right))
            pos_x++;
        character = '>';
        break;
    case ARROW_RIGHT:
        character = '>';
        sword.attack(ch);
        break;
    case ESC:
        armor -= armor;
        getDamage(max_HP);
    }

    lastPressedKey = std::tolower(ch);
}

void Player::controller()
{
    char ch = '\0';
    if (_kbhit())
        ch = _getch();

    switch (ch)
    {
    case w:
    case W:
        pos_y--;
        character = '^';
        break;
    case a:
    case A:
        pos_x--;
        character = '<';
        break;
    case s:
    case S:
        pos_y++;
        character = 'V';
        break;
    case d:
    case D:
        pos_x++;
        character = '>';
        break;
    case i:
    case I:
        Level::upgrade(*this);
        break;
    case ESC:
        armor -= armor;
        getDamage(max_HP);
    }

    lastPressedKey = std::tolower(ch);
}

char Player::draw()
{
    return character;
}

void Player::getDamage(int dmg)
{
    Character::getDamage(dmg);
    
    debug::log->request("The player has taken " + std::to_string(dmg) + " points of damage\n\n");
    if (!status)
        debug::log->request("The player died on x: " + std::to_string(pos_x) + " y: " + std::to_string(pos_y) + " coordinates\n\n");
}

char Player::getLastPressedKey()
{
    return lastPressedKey;
}

int Player::getStrength()
{
    return strength;
}

void Player::increaseStrength()
{
    strength++;
}

void Player::heal()
{
    HP++;
}

void Player::increaseMaxHP()
{
    max_HP++;
}

void Player::fixArmor()
{
    armor++;
}

int Player::getMoney()
{
    return money;
}

void Player::setMoney(int m)
{
    money = m;
}

bool Player::drawSword(int x, int y)
{
    Sword s(this);
    if (Sword::getPos_x() == x && Sword::getPos_y() == y)
    {
        gotoPoint(x, y);
        s.draw();
        return true;
    }
    return false;
}

void Player::addMoney(int m)
{
    money += m;
}
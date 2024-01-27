#pragma once

#include "Character.h"

class Player final : public Character
{
    enum buttons
    {
        //spec
        ENTER = 13,
        ESC   = 27,
        SPACE = 32,
        //arrows
        ARROW_UP    = 72,
        ARROW_LEFT  = 75,
        ARROW_RIGHT = 77,
        ARROW_DOWN  = 80,
        //controllers
        A = 65,
        D = 68,
        E = 69,
        I = 73,
        Q = 81,
        S = 83,
        W = 87,

        a = 97,
        d = 100,
        e = 101,
        i = 105,
        q = 113,
        s = 115,
        w = 119,
    };

    int strength = 1;
    int money = 0;

    char lastPressedKey = '\0';
public:
    Player();

    ~Player();

    void controller(int, int, int, int);

    void getDamage(int);

    void controller();

    char draw();

    char getLastPressedKey();

    int getStrength();

    void increaseStrength();

    void heal();

    void increaseMaxHP();

    void fixArmor();

    int getMoney();

    void setMoney(int);

    bool drawSword(int, int);

    void addMoney(int);
};
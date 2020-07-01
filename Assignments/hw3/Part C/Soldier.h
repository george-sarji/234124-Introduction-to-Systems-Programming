#ifndef SOLDIER_H
#define SOLDIER_H

#include "Character.h"

namespace mtm
{
    class Soldier : public Character
    {
    public:
        Soldier(int range, int ammo, int health, int power) : Character(health, ammo, range, power, 3, 1, 3) {}
    };
} // namespace mtm

#endif
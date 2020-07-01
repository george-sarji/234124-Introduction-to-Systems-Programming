#ifndef SNIPER_H
#define SNIPER_H

#include "Character.h"

namespace mtm
{
    class Sniper : public Character
    {
    public:
        explicit Sniper(int health, int ammo, int range, int power) : Character(health, ammo, range, power, 4, 1, 2);
    };
}; // namespace mtm

#endif
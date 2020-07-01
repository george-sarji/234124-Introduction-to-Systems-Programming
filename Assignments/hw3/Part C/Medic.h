#ifndef MEDIC_H
#define MEDIC_H

#include "Character.h"

namespace mtm
{
    class Medic : public Character
    {
    public:
        explicit Medic(int health, int ammo, int range, int power) : Character(health, ammo, range, power, 5, 1, 5) {}
    };
}; // namespace mtm

#endif
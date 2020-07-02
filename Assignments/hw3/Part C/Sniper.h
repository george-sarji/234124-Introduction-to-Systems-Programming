#ifndef SNIPER_H
#define SNIPER_H

#include "Character.h"
#include "Auxiliaries.h"

namespace mtm
{
    class Sniper : public Character
    {
    public:
        Sniper(int ammo, int health, int range, int power, Team team) : Character(ammo, health, range, power, 4, 2, 1, team, SNIPER) {}
        Sniper(const Sniper &sniper) : Character(sniper) {}
        bool isAttackValid(GridPoint source, GridPoint destination) const override;
        void attack(const GridPoint& src, const GridPoint &dest) const override;

        std::shared_ptr<Character> clone() const override;
    };
}; // namespace mtm

#endif
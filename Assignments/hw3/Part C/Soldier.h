#ifndef SOLDIER_H
#define SOLDIER_H

#include "Character.h"
#include "Auxiliaries.h"
#include <memory>

namespace mtm
{
    class Soldier : public Character
    {
    public:
        Soldier(units_t ammo, units_t health, units_t range, units_t power, Team team) : Character(ammo, health, range, power, 3, 3, 1, team, SOLDIER) {}
        Soldier(const Soldier &soldier) : Character(soldier) {}
        bool isAttackValid(GridPoint source, GridPoint destination) const override;
        void attack(const GridPoint& src, const GridPoint &dest) const override;

        std::shared_ptr<Character> clone() const override;
    };
}; // namespace mtm

#endif
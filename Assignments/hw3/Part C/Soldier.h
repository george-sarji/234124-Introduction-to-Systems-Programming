#ifndef SOLDIER_H
#define SOLDIER_H

#include "Character.h"
#include "Matrix.h"
#include "Auxiliaries.h"
#include <memory>
#include <list>

#define SOLDIER_MOVE_RANGE 3
#define SOLDIER_RELOAD 3
#define SOLDIER_ATTACK_COST 1

namespace mtm
{
    class Soldier : public Character
    {
    public:
        Soldier(units_t ammo, units_t health, units_t range, units_t power, Team team) : Character(ammo, health, range, power,
                                                                                                   3, 3,
                                                                                                   1, team, SOLDIER) {}
        Soldier(const Soldier &soldier) = default;
        std::list<std::shared_ptr<Character>> attack(const GridPoint &source, const GridPoint &dest, const Matrix<std::shared_ptr<Character>> &grid) const override;

        std::shared_ptr<Character> clone() const override;
    };
}; // namespace mtm

#endif
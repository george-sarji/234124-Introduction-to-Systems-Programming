#ifndef SNIPER_H
#define SNIPER_H

#include "Character.h"
#include "Matrix.h"
#include "Auxiliaries.h"
#include <memory>
#include <list>

#define SNIPER_MOVE_RANGE 4
#define SNIPER_RELOAD 2
#define SNIPER_ATTACK_COST 1

namespace mtm
{
    class Sniper : public Character
    {

    public:
        Sniper(int ammo, int health, int range, int power, Team team) : Character(ammo, health, range, power,
                                                                                  4, 2,
                                                                                  1, team, SNIPER) {}
        Sniper(const Sniper &other) = default;
        std::list<std::shared_ptr<Character>> attack(const GridPoint &source, const GridPoint &dest, const Matrix<std::shared_ptr<Character>> &grid) const override;

        std::shared_ptr<Character> clone() const override;
    };
}; // namespace mtm

#endif
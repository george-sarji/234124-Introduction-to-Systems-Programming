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
        Soldier(units_t health, units_t ammo, units_t range, units_t power, Team team);
        Soldier(const Soldier &soldier) = default;
        void attack(const GridPoint &source, const GridPoint &dest,
                    const Matrix<std::shared_ptr<Character>> &grid) override;

        std::shared_ptr<Character> clone() const override;
    };
}; // namespace mtm

#endif
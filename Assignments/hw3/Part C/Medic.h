#ifndef MEDIC_H
#define MEDIC_H

#include "Character.h"
#include "Matrix.h"
#include "Auxiliaries.h"
#include <memory>
#include <list>

#define MEDIC_MOVE_RANGE 5
#define MEDIC_RELOAD 5
#define MEDIC_ATTACK_COST 1

namespace mtm
{
    class Medic : public Character
    {

    public:
        Medic(units_t ammo, units_t health, units_t range, units_t power, Team team);
        Medic(const Medic &medic) = default;
        void attack(const GridPoint &source, const GridPoint &dest, const Matrix<std::shared_ptr<Character>> &grid) override;

        std::shared_ptr<Character> clone() const override;
    };
}; // namespace mtm

#endif
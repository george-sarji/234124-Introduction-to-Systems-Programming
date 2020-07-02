#ifndef MEDIC_H
#define MEDIC_H

#include "Character.h"
#include "Matrix.h"
#include "Auxiliaries.h"
#include <memory>
#include <list>

namespace mtm
{
    class Medic : public Character
    {
    public:
        Medic(units_t ammo, units_t health, units_t range, units_t power, Team team) : Character(ammo, health, range, power, 5, 5, 1, team, MEDIC) {}
        Medic(const Medic &medic) : Character(medic) {}
        std::list<std::shared_ptr<Character>> attack(const GridPoint &source, const GridPoint &dest, const Matrix<std::shared_ptr<Character>> &grid) const override;

        std::shared_ptr<Character> clone() const override;
    };
}; // namespace mtm

#endif
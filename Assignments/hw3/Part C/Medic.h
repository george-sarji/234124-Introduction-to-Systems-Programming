#ifndef MEDIC_H
#define MEDIC_H

#include "Character.h"
#include "Auxiliaries.h"
#include <memory>

namespace mtm
{
    class Medic : public Character
    {
    public:
        Medic(units_t ammo, units_t health, units_t range, units_t power, Team team) : Character(ammo, health, range, power, 5, 5, 1, team, MEDIC) {}
        Medic(const Medic &medic) : Character(medic) {}
        bool isAttackValid(GridPoint source, GridPoint destination) const override;
        void attack(const GridPoint &src, const GridPoint &dest) const override;

        std::shared_ptr<Character> clone() const override;
    };
}; // namespace mtm

#endif
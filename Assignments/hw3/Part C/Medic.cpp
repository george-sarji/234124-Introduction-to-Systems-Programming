#include "Medic.h"
#include "Auxiliaries.h"
namespace mtm
{
    mtm::Medic::Medic(units_t ammo, units_t health, units_t range, units_t power, Team team) : Character(ammo, health, range, power,
                                                                                                         5, 5, 1, team, MEDIC) {}

    std::shared_ptr<Character> mtm::Medic::clone() const
    {
        return std::shared_ptr<Character>(new Medic(*this));
    }
    std::list<std::shared_ptr<Character>> mtm::Medic::attack(const GridPoint &source, const GridPoint &dest, const Matrix<std::shared_ptr<Character>> &grid) const
    {
        std::list<std::shared_ptr<Character>> affected;
        return affected;
    }
} // namespace mtm
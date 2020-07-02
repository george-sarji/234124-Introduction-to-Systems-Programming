#include "Medic.h"
#include "Auxiliaries.h"
#include "Exceptions.h"
namespace mtm
{
    mtm::Medic::Medic(units_t ammo, units_t health, units_t range, units_t power, Team team) : Character(ammo, health, range, power,
                                                                                                         5, 5, 1, team, MEDIC) {}

    std::shared_ptr<Character> mtm::Medic::clone() const
    {
        return std::shared_ptr<Character>(new Medic(*this));
    }
    void mtm::Medic::attack(const GridPoint &source, const GridPoint &dest, const Matrix<std::shared_ptr<Character>> &grid)
    {
        // The shot is in range. We need to check if there is someone in the destination.
        std::shared_ptr<Character> &target = grid(dest.row, dest.col);
        // Check if the target is empty.
        if (!target)
        {
            throw IllegalTarget();
        }
        // Check if the target is a friendly or not.
        if ((*target).getTeam() == getTeam())
        {
            // Heal the target.
            (*target).heal(getPower());
        }
        else
        {
            // Shoot.
            shoot();
            (*target).addDamage(getPower());
            // Check if target is dead.
            if (!(*target).isAlive())
            {
                // Target is dead. Disqualify.
                target.reset();
            }
        }
    }
} // namespace mtm
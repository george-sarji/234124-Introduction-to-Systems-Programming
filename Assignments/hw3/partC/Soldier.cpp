#include "Soldier.h"
#include "Character.h"
#include "Auxiliaries.h"
#include <memory>
#include <list>
#include "Exceptions.h"

namespace mtm
{
    // Soldier constructor, uses default values for move range, attack cost and reload amount.
    mtm::Soldier::Soldier(units_t health, units_t ammo, units_t range, units_t power, Team team) : Character(health, ammo, range,
                                                                                                             power, 3, 3,
                                                                                                             1, team, SOLDIER) {}

    // Attack function, handles the logic for a soldier attack.
    void mtm::Soldier::attack(const GridPoint &source, const GridPoint &dest, const Matrix<std::shared_ptr<Character>> &grid)
    {
        // First check if we can even attack dest
        if (isOutOfAmmo())
        {
            throw OutOfAmmo();
        }
        if ((source.col != dest.col && source.row != dest.row))
        {
            throw IllegalTarget();
        }
        // Legal shot. Remove one ammo.
        shoot();
        // Check if the destination has an enemy.
        std::shared_ptr<Character> &target = grid(dest.row, dest.col);
        if (grid(source.row, source.col) != target && target)
        {
            // We have a target in the destination grid. Damage.
            target->addDamage(getPower());
            // Check if the target is dead.
            if (!target->isAlive())
            {
                // Disqualify.
                target.reset();
            }
        }
        // We need to iterate through a sub-matrix within the splash damage zone
        // Get the range that the splash zone will have
        units_t splash_range = getRange() % 3 == 0 ? getRange() / 3 : getRange() / 3 + 1;
        units_t splash_damage = getPower() % 3 == 0 ? getPower() / 3 : getPower() / 3 + 1;
        // We need to get the submatrix
        // Get the beginning row and col
        int beginning_row = dest.row - splash_range < 0 ? 0 : dest.row - splash_range;
        int beginning_col = dest.col - splash_range < 0 ? 0 : dest.col - splash_range;
        // Get the ending row and col
        int ending_row = dest.row + splash_range >= grid.height() ? grid.height() - 1 : dest.row + splash_range;
        int ending_col = dest.col + splash_range >= grid.width() ? grid.width() - 1 : dest.col + splash_range;
        // Iterate through the sub-matrix
        for (int i = beginning_row; i <= ending_row; i++)
        {
            for (int j = beginning_col; j <= ending_col; j++)
            {
                // Check if we are in a legal cell
                if (GridPoint::distance(dest, GridPoint(i, j)) > splash_range)
                {
                    continue;
                }
                std::shared_ptr<Character> &current = grid(i, j);
                // Check if we have a character in the current cell
                if (current)
                {
                    // We have a character in this grid. Only attack non-team mates
                    if (current->getTeam() != getTeam())
                    {
                        // Damage this character.
                        current->addDamage(splash_damage);
                        // Add the current to the affected list.
                        // Check if the target is dead.
                        if (!current->isAlive())
                        {
                            // Change to a nullptr.
                            current.reset();
                        }
                    }
                }
            }
        }
    }
    // Clone function, used for copying.
    std::shared_ptr<Character> mtm::Soldier::clone() const
    {
        // Create a new copy of the current soldier
        return std::shared_ptr<Character>(new Soldier(*this));
    }
} // namespace mtm
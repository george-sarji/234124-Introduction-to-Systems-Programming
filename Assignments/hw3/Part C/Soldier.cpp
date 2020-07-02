#include "Soldier.h"
#include "Character.h"
#include "Auxiliaries.h"
#include <memory>
#include <list>
#include "Exceptions.h"

namespace mtm
{

    std::list<std::shared_ptr<Character>> mtm::Soldier::attack(const GridPoint &source, const GridPoint &dest, const Matrix<std::shared_ptr<Character>> &grid) const
    {
        std::list<std::shared_ptr<Character>> affected;
        // First check if we can even attack dest
        if ((source.col != dest.col && source.row != dest.row) || !isInAttackRange(source, dest))
        {
            throw OutOfRange();
        }
        // Check if the destination has an enemy.
        std::shared_ptr<Character> target = grid(dest.row, dest.col);
        if (target)
        {
            // We have a target in the destination grid. Damage.
            (*target).addDamage(getPower());
            affected.push_front(target);
        }
        // We need to iterate through a sub-matrix within the splash damage zone
        // Get the range that the splash zone will have
        units_t splash_range = std::round(getRange() / 3);
        units_t splash_damage = std::round(getPower() / 2);
        // We need to get the submatrix
        return affected;
    }
    std::shared_ptr<Character> mtm::Soldier::clone() const
    {

        // Create a new copy of the current soldier
        return std::shared_ptr<Character>(new Soldier(*this));
    }
} // namespace mtm
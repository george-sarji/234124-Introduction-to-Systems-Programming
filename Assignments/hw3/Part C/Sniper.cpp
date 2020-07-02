#include "Sniper.h"
#include <memory>
#include "Exceptions.h"
#include "Auxiliaries.h"
namespace mtm
{
    void mtm::Sniper::attack(const GridPoint &source, const GridPoint &dest, const Matrix<std::shared_ptr<Character>> &grid)
    {
        // The point is in attack range, but is it away in the minimal distance?
        units_t minimum_range = std::round(getRange() / 2);
        if (mtm::GridPoint::distance(source, dest) < minimum_range)
        {
            // Illegal point. Throw an exception.
            throw OutOfRange();
        }
        // OK. We're in range. Check if there is an opponent in the destination.
        std::shared_ptr<Character> &target = grid(dest.row, dest.col);
        // Check if it's empty, or if it's a friendly.
        if (!target || (*target).getTeam() == getTeam())
        {
            // Illegal target. Throw an exception.
            throw IllegalTarget();
        }
        // There's an enemy in that grid. Shoot.
        shoot();
        shots_counter++;
        units_t damage = getPower();
        if (shots_counter == 3)
        {
            // Three shots. Double damage.
            damage *= 2;
        }
        // Remove from the health of the target.
        (*target).addDamage(damage);
        // Check if target is dead.
        if (!(*target).isAlive())
        {
            // Disqualify.
            target.reset();
        }
    }
    std::shared_ptr<Character> mtm::Sniper::clone() const
    {
        return std::shared_ptr<Character>(new Sniper(*this));
    }

} // namespace mtm
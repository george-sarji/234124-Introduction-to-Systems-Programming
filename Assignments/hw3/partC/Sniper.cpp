#include "Sniper.h"
#include <memory>
#include "Exceptions.h"
#include "Auxiliaries.h"
namespace mtm
{
    // Constructor for sniper, uses default values for move range, attack cost and reload amount
    mtm::Sniper::Sniper(int health, int ammo, int range, int power, Team team) : Character(health, ammo, range, power,
                                                                                           4, 2,
                                                                                           1, team, SNIPER) {}

    // Attack function, handles the attack logic for a sniper
    void mtm::Sniper::attack(const GridPoint &source, const GridPoint &dest, const Matrix<std::shared_ptr<Character>> &grid)
    {
        // The point is in attack range, but is it away in the minimal distance?
        units_t minimum_range = getRange() % 2 == 0 ? getRange() / 2 : getRange() / 2 + 1;
        if (mtm::GridPoint::distance(source, dest) < minimum_range)
        {
            // Illegal point. Throw an exception.
            throw OutOfRange();
        }
        // Check if sniper is out of ammo
        if (isOutOfAmmo())
        {
            throw OutOfAmmo();
        }
        // OK. We're in range and we have ammo. Check if there is an opponent in the destination.
        std::shared_ptr<Character> &target = grid(dest.row, dest.col);
        // Check if it's empty, or if it's a friendly.
        if (!target || target->getTeam() == getTeam())
        {
            // Illegal target. Throw an exception.
            throw IllegalTarget();
        }
        // There's an enemy in that grid. Shoot.
        shoot();
        // Increase the shots counter
        shots_counter++;
        units_t damage = getPower();
        // Is this our 3rd shot in a row?
        if (shots_counter == 3)
        {
            // Three shots. Double damage.
            damage *= 2;
            // Reset the counter.
            shots_counter = 0;
        }
        // Remove from the health of the target.
        target->addDamage(damage);
        // Check if target is dead.
        if (!target->isAlive())
        {
            // Disqualify.
            target.reset();
        }
    }

    // Clone, used for copying.
    std::shared_ptr<Character> mtm::Sniper::clone() const
    {
        return std::shared_ptr<Character>(new Sniper(*this));
    }

} // namespace mtm
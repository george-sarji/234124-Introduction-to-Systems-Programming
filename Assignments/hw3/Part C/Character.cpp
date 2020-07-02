#include "Character.h"
#include "Auxiliaries.h"
#include "Soldier.h"

namespace mtm
{
    bool mtm::Character::isInMoveRange(GridPoint source, GridPoint destination) const
    {
        // Check the distance between the two points, and whether they're out of the move range
        return source.distance(source, destination) <= move_range;
    }

    bool mtm::Character::isInAttackRange(GridPoint source, GridPoint destination) const
    {
        // Check the distance between the two points, and whether they're out of the move range
        return source.distance(source, destination) <= range;
    }

    bool mtm::Character::isMoveValid(GridPoint source, GridPoint destination) const
    {
        return isInMoveRange(source, destination);
    }
    bool mtm::Character::isAlive() const
    {
        return health > 0;
    }
    bool mtm::Character::isOutOfAmmo() const
    {
        return ammo < attack_cost;
    }
    units_t mtm::Character::getAmmo() const
    {
        return ammo;
    }
    units_t mtm::Character::getHealth() const
    {
        return health;
    }
    units_t mtm::Character::getRange() const
    {
        return range;
    }
    units_t mtm::Character::getPower() const
    {
        return power;
    }
    units_t mtm::Character::getMoveRange() const
    {
        return move_range;
    }
    units_t mtm::Character::getReloadAmount() const
    {
        return reload_amount;
    }
    units_t mtm::Character::getAttackCost() const
    {
        return attack_cost;
    }
    Team mtm::Character::getTeam() const
    {
        return team;
    }
    CharacterType mtm::Character::getType() const
    {
        return type;
    }

    void mtm::Character::reloadAmmo()
    {
        ammo += reload_amount;
    }

} // namespace mtm
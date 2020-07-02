#include "Character.h"
#include "Auxiliaries.h"
#include "Soldier.h"

namespace mtm
{

    mtm::Character::Character(units_t health, units_t ammo, units_t range, units_t power, units_t move_range, units_t reload_amount, units_t attack_cost,
                              Team team, CharacterType type) : health(health), ammo(ammo), range(range), power(power),
                                                               move_range(move_range), reload_amount(reload_amount),
                                                               attack_cost(attack_cost), team(team), type(type) {}
    bool mtm::Character::isInMoveRange(GridPoint source, GridPoint destination) const
    {
        // Check the distance between the two points, and whether they're out of the move range
        return mtm::GridPoint::distance(source, destination) <= move_range;
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

    void mtm::Character::addDamage(int damage)
    {
        health -= damage;
    }

    void mtm::Character::heal(int hp)
    {
        health += hp;
    }

    void mtm::Character::shoot()
    {
        ammo -= attack_cost;
    }

} // namespace mtm
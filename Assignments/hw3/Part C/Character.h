#ifndef CHARACTER_H
#define CHARACTER_H

#include "Auxiliaries.h"
#include <memory>

namespace mtm
{
    class Character
    {
    private:
        units_t ammo, health, range, power, move_range, reload_amount, attack_cost;
        Team team;
        CharacterType type;

    protected:
        Character(units_t ammo, units_t health, units_t range, units_t power, units_t move_range, units_t reload_amount, units_t attack_cost,
                  Team team, CharacterType type) : ammo(ammo), health(health), range(range), power(power),
                                                   move_range(range), reload_amount(reload_amount),
                                                   attack_cost(attack_cost), team(team), type(type) {}
        Character(const Character &character) : ammo(character.ammo), health(character.health), range(character.range),
                                                power(character.power), move_range(character.move_range),
                                                reload_amount(character.reload_amount), attack_cost(character.attack_cost),
                                                team(character.team), type(character.type) {}

    public:
        virtual std::shared_ptr<Character> clone() const = 0;
        virtual bool isAttackValid(GridPoint source, GridPoint destination) const = 0;
        virtual void attack(const GridPoint& src, const GridPoint& dest) const = 0;
        bool isMoveValid(GridPoint source, GridPoint destination) const;
        bool isAlive() const;
        bool isOutOfAmmo() const;
        bool isInMoveRange(GridPoint source, GridPoint destination) const;
        bool isInAttackRange(GridPoint source, GridPoint destination) const;
        void reloadAmmo();

        // ! Getters/Setters
        units_t getAmmo() const;
        units_t getHealth() const;
        units_t getRange() const;
        units_t getPower() const;
        units_t getMoveRange() const;
        units_t getReloadAmount() const;
        units_t getAttackCost() const;
        Team getTeam() const;
        CharacterType getType() const;
    };
}; // namespace mtm

#endif
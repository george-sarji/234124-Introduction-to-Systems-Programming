#ifndef CHARACTER_H
#define CHARACTER_H

#include "Matrix.h"
#include <memory>
#include <list>

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
                  Team team, CharacterType type);
        Character(const Character &character) = default;
        virtual ~Character() = default;

    public:
        virtual std::shared_ptr<Character> clone() const = 0;
        bool isMoveValid(GridPoint source, GridPoint destination) const;
        virtual void attack(const GridPoint &source, const GridPoint &dest, const Matrix<std::shared_ptr<Character>> &grid) = 0;
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

        void addDamage(int damage);
        void heal(int hp);
        void shoot();
    };
}; // namespace mtm

#endif
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
        // Structure of character:
        // Has the following:
        // Ammo (integer) - Denotes ammo left
        // Health (integer) - Denotes HP left
        // Range (integer) - Denotes attack range
        // Power (integer) - Denotes damaage done on attack
        // Move Range (integer) - Denotes range of movement
        // Reload amount (integer) - Denotes amount received upon reload
        // Attack cost (integer) - Denotes amount of ammo used per attack
        // Team (Team) - Denotes which team the character is on
        // Type (CharacterType) - Denotes what type the character is.
        units_t ammo, health, range, power, move_range, reload_amount, attack_cost;
        Team team;
        CharacterType type;

    protected:
        // Protected constructors to ensure this class can't be constructed without inheritence.
        Character(units_t health, units_t ammo, units_t range, units_t power, units_t move_range, units_t reload_amount, units_t attack_cost,
                  Team team, CharacterType type);
        Character(const Character &character) = default;
        virtual ~Character() = default;

    public:
        // Clone function, used for copying.
        virtual std::shared_ptr<Character> clone() const = 0;
        // Attack function, handles each character class attack logic
        virtual void attack(const GridPoint &source, const GridPoint &dest, const Matrix<std::shared_ptr<Character>> &grid) = 0;
        // Returns whether character is still alive or not
        bool isAlive() const;
        // Returns whether the character is out of ammo
        bool isOutOfAmmo() const;
        // Returns whether the character is within move range from source to destination
        bool isInMoveRange(GridPoint source, GridPoint destination) const;
        // Returns whether the character is within attack range from source to destination
        bool isInAttackRange(GridPoint source, GridPoint destination) const;
        // Reloads the ammo of the character
        void reloadAmmo();

        // ! Getters/Setters
        // Retrieves the attack range
        units_t getRange() const;
        // Retrieves the attack damage
        units_t getPower() const;
        // Retrieves the team
        Team getTeam() const;
        // Retrieves the type
        CharacterType getType() const;
        // Damages the character
        void addDamage(int damage);
        // Heals the character
        void heal(int hp);
        // Registers an active shot
        void shoot();
    };
}; // namespace mtm

#endif
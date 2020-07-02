#ifndef SNIPER_H
#define SNIPER_H

#include "Character.h"
#include "Matrix.h"
#include "Auxiliaries.h"
#include <memory>
#include <list>

#define SNIPER_MOVE_RANGE 4
#define SNIPER_RELOAD 2
#define SNIPER_ATTACK_COST 1

namespace mtm
{
    class Sniper : public Character
    {
    private:
        int shots_counter = 0;

    public:
        Sniper(int health, int ammo, int range, int power, Team team);
        Sniper(const Sniper &other) = default;
        void attack(const GridPoint &source, const GridPoint &dest, const Matrix<std::shared_ptr<Character>> &grid) override;
        std::shared_ptr<Character> clone() const override;
    };
}; // namespace mtm

#endif
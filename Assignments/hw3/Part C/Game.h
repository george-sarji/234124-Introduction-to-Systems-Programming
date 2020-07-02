#ifndef GAME_H
#define GAME_H

#include "Matrix.h"
#include <memory>
#include "Character.h"
#include "Sniper.h"
#include "Medic.h"
#include "Soldier.h"

namespace mtm
{
    class Game
    {
    private:
        Matrix<std::shared_ptr<Character>> game_grid;
        int rows, cols;
        std::shared_ptr<Character> &getGridPoint(const GridPoint &coords);
        bool isInGameBounds(const GridPoint &coords);

    public:
        Game(int height, int width);
        ~Game() = default;
        Game(const Game &game);
        Game &operator=(const Game &other);

        void addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character);
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team, units_t health, units_t ammo, units_t range, units_t power);
        void move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);
        void attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);
        void reload(const GridPoint &coordinates);
        bool isOver(Team *winningTeam = NULL) const;

        friend std::ostream &operator<<(std::ostream &stream, const Game &game);
    };
}; // namespace mtm

#endif
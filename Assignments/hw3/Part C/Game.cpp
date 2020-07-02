#include "Game.h"
#include "Exceptions.h"
#include "Auxiliaries.h"
#include <list>
#include <memory>

namespace mtm
{
    mtm::Game::Game(int height, int width) : game_grid(Dimensions(height, width))
    {
        // Check if the width or height are out of bounds
        if (height <= 0 || width <= 0)
        {
            throw IllegalArgument();
        }
        rows = height;
        cols = width;
        // Else, create the matrix as required.
    }

    std::shared_ptr<Character> &mtm::Game::getGridPoint(const GridPoint &coords)
    {
        return game_grid(coords.row, coords.col);
    }

    mtm::Game::Game(const Game &other) : game_grid(other.game_grid)
    {
        // Copy constructor, copy the matrix.
        rows = other.rows;
        cols = other.cols;
        // We copied the grid. We have to refill the contents however.
        for (int i = 0; i < game_grid.height(); i++)
        {
            for (int j = 0; j < game_grid.width(); j++)
            {
                // Re-fill the contents with new pointers to the clones.
                if (game_grid(i, j))
                {
                    game_grid(i, j) = std::shared_ptr<Character>((*game_grid(i, j)).clone());
                }
                else
                {
                    game_grid(i, j) = std::shared_ptr<Character>();
                }
            }
        }
    }

    Game &mtm::Game::operator=(const Game &other)
    {
        rows = other.rows;
        cols = other.cols;
        // Delete the current grid.
        game_grid = other.game_grid;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                std::shared_ptr<Character> current = game_grid(i, j);
                if (current)
                {
                    game_grid(i, j) = current->clone();
                }
                else
                {
                    game_grid(i, j) = std::shared_ptr<Character>();
                }
            }
        }
        return (*this);
        // Create a new grid according to the new width and height.
    }
    void mtm::Game::addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character)
    {
        if (!isInGameBounds(coordinates))
        {
            throw IllegalCell();
        }
        // Check if the point is already occupied.
        std::shared_ptr<Character> &grid = getGridPoint(coordinates);
        if (grid != NULL)
        {
            // Already taken. Throw an error
            throw CellOccupied();
        }
        else
        {
            // Grid empty. Assign.
            grid.swap(character);
        }
    }

    std::shared_ptr<Character> mtm::Game::makeCharacter(CharacterType type, Team team, units_t health, units_t ammo, units_t range, units_t power)
    {
        // Check if all parameters are legal
        if (health <= 0 || ammo < 0 || range < 0 || power < 0)
        {
            throw IllegalArgument();
        }
        // Create a new character according to the type
        switch (type)
        {
        case SNIPER:
        {
            return std::shared_ptr<Character>(new Sniper(health, ammo, range, power, team));
        }
        case MEDIC:
        {
            return std::shared_ptr<Character>(new Medic(health, ammo, range, power, team));
        }
        case SOLDIER:
        {
            return std::shared_ptr<Character>(new Soldier(health, ammo, range, power, team));
        }
        }
        // We did not reach any types. Something's wrong. Return null, as we shouldn't arrive here.
        return NULL;
    }

    bool mtm::Game::isInGameBounds(const GridPoint &coords)
    {
        return coords.row >= 0 && coords.row < rows && coords.col >= 0 && coords.col < cols;
    }

    void mtm::Game::move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {
        // Check if the coordinates are in bounds
        if (!isInGameBounds(src_coordinates) || !isInGameBounds(dst_coordinates))
        {
            throw IllegalCell();
        }
        std::shared_ptr<Character> &character = getGridPoint(src_coordinates);
        // Check if there is a character in the source point
        if (!character)
        {
            throw CellEmpty();
        }
        // Check if the move is valid for the given character.
        if (!character->isInMoveRange(src_coordinates, dst_coordinates))
        {
            throw MoveTooFar();
        }
        // Check if we can move to the destination (no characters in destination)
        std::shared_ptr<Character> &destination = getGridPoint(dst_coordinates);
        if (destination && destination != character)
        {
            throw CellOccupied();
        }
        // We can move the character to the designated spot.
        destination.swap(character);
    }
    void mtm::Game::attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates)
    {
        // Check if source and destination are legal
        if (!isInGameBounds(src_coordinates) || !isInGameBounds(dst_coordinates))
        {
            throw IllegalCell();
        }
        // Check if the source is empty.
        std::shared_ptr<Character> &source_char = getGridPoint(src_coordinates);
        if (!source_char)
        {
            throw CellEmpty();
        }
        // Check if the destination is even in attack range
        if (!(*source_char).isInAttackRange(src_coordinates, dst_coordinates))
        {
            // Not in range. Throw out of range.
            throw OutOfRange();
        }
        // Check if the attacker is out of ammo.
        // Attack the destination (check exceptions in character-specific attacks)
        // TODO: Continue logic for attack
        // Use std::vector to return list of affected characters
        // Use character specific attacks to update game board with effects etc
        // Return map<damage, std::vector<map<GridPoint, Character>>>
        // Each dm
        (*source_char).attack(src_coordinates, dst_coordinates, game_grid);
    }

    void mtm::Game::reload(const GridPoint &coordinates)
    {
        // Check if the point is in bounds
        if (!isInGameBounds(coordinates))
        {
            throw IllegalCell();
        }
        // Check if there is someone in the given coordinate.
        std::shared_ptr<Character> character = getGridPoint(coordinates);
        if (!character)
        {
            throw CellEmpty();
        }
        // No problems. Reload ammo.
        (*character).reloadAmmo();
    }

    bool mtm::Game::isOver(Team *winningTeam) const
    {
        bool cppAlive = false, pythonAlive = false;
        for (int i = 0; i < game_grid.height(); i++)
        {
            for (int j = 0; j < game_grid.width(); j++)
            {
                if (game_grid(i, j))
                {
                    // Check which team.
                    if ((*game_grid(i, j)).getTeam() == mtm::CPP)
                    {
                        cppAlive = true;
                    }
                    else
                    {
                        pythonAlive = true;
                    }
                    if (cppAlive && pythonAlive)
                    {
                        return false;
                    }
                }
            }
        }
        if (!pythonAlive && !cppAlive)
        {
            return false;
        }
        if (winningTeam != NULL)
        {
            *winningTeam = cppAlive ? mtm::CPP : mtm::PYTHON;
        }
        return true;
    }

    std::ostream &operator<<(std::ostream &stream, const Game &game)
    {
        char *characters = new char[game.game_grid.size()];
        int index = 0;
        //  Iterate through the game board.
        for (int i = 0; i < game.game_grid.height(); i++)
        {
            for (int j = 0; j < game.game_grid.width(); j++)
            {
                std::shared_ptr<Character> current = game.game_grid(i, j);
                if (current)
                {
                    switch ((*current).getType())
                    {
                    case MEDIC:
                    {
                        characters[index] = ((*current).getTeam() == mtm::CPP) ? 'M' : 'm';
                        break;
                    }
                    case SNIPER:
                    {
                        characters[index] = ((*current).getTeam() == mtm::CPP) ? 'N' : 'n';
                        break;
                    }
                    case SOLDIER:
                    {
                        characters[index] = ((*current).getTeam() == mtm::CPP) ? 'S' : 's';
                        break;
                    }
                    }
                }
                else
                {
                    characters[index] = ' ';
                }
                index++;
            }
        }
        printGameBoard(stream, &characters[0], &characters[index], game.game_grid.width());
        delete[] characters;
        return stream;
    }

}; // namespace mtm
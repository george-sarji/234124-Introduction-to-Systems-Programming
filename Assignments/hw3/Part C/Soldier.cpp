#include "Soldier.h"
#include "Character.h"
#include "Auxiliaries.h"
#include <memory>

namespace mtm
{
    bool mtm::Soldier::isAttackValid(GridPoint src, GridPoint dest) const
    {
        // Check if the destination is in the same row or column.
        if (src.row != dest.row || src.col != dest.col)
        {
            return false;
        }
        // Check if the destination is within attack range
        return isInAttackRange(src, dest);
    }
    std::shared_ptr<Character> mtm::Soldier::clone() const
    {

        // Create a new copy of the current soldier
        return std::shared_ptr<Character>(new Soldier(*this));
    }
} // namespace mtm
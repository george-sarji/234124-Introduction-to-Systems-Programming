#include "Sniper.h"
#include <memory>
#include "Auxiliaries.h"
namespace mtm
{
    bool mtm::Sniper::isAttackValid(GridPoint source, GridPoint destination) const
    {
        return true;
    }

    std::shared_ptr<Character> mtm::Sniper::clone() const
    {
        return std::shared_ptr<Character>(new Sniper(*this));
    }
} // namespace mtm
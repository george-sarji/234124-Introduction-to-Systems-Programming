#include "Medic.h"
namespace mtm
{
    std::shared_ptr<Character> mtm::Medic::clone() const
    {
        return std::shared_ptr<Character>(new Medic(*this));
    }

    bool mtm::Medic::isAttackValid(GridPoint src, GridPoint dest) const
    {
        return true;
    }
} // namespace mtm
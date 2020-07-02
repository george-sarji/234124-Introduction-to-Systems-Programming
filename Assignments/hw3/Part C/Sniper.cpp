#include "Sniper.h"
#include <memory>
#include "Auxiliaries.h"
namespace mtm
{
    std::list<std::shared_ptr<Character>> mtm::Sniper::attack(const GridPoint &source, const GridPoint &dest, const Matrix<std::shared_ptr<Character>> &grid) const
    {
        std::list<std::shared_ptr<Character>> affected;
        return affected;
    }
    std::shared_ptr<Character> mtm::Sniper::clone() const
    {
        return std::shared_ptr<Character>(new Sniper(*this));
    }

} // namespace mtm
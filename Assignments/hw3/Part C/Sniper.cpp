#include "Sniper.h"
#include <memory>
#include "Auxiliaries.h"
namespace mtm
{

    std::shared_ptr<Character> mtm::Sniper::clone() const
    {
        return std::shared_ptr<Character>(new Sniper(*this));
    }

} // namespace mtm
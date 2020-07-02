#include "Exceptions.h"

namespace mtm
{
    const char *mtm::IllegalArgument::what() const noexcept
    {
        return "A game related error has occured: IllegalArgument";
    }

    const char *mtm::IllegalCell::what() const noexcept
    {
        return "A game related error has occured: IllegalCell";
    }

    const char *mtm::CellEmpty::what() const noexcept
    {
        return "A game related error has occured: CellEmpty";
    }

    const char *mtm::MoveTooFar::what() const noexcept
    {
        return "A game related error has occured: MoveTooFar";
    }

    const char *mtm::CellOccupied::what() const noexcept
    {
        return "A game related error has occured: CellOccupied";
    }

    const char *mtm::OutOfRange::what() const noexcept
    {
        return "A game related error has occured: OutOfRange";
    }

    const char *mtm::OutOfAmmo::what() const noexcept
    {
        return "A game related error has occured: OutOfAmmo";
    }

    const char *mtm::IllegalTarget::what() const noexcept
    {
        return "A game related error has occured: IllegalTarget";
    }
} // namespace mtm
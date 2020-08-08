#include "Exceptions.h"

namespace mtm
{

    const char *mtm::GraphException::what() const noexcept
    {
        return "Error.";
    }
    const char *mtm::IllegalName::what() const noexcept
    {
        return "Error: Illegal vertex name.";
    }
    const char *mtm::DuplicateVertex::what() const noexcept
    {
        return "Error: Duplicate vertex name.";
    }

    const char *mtm::SelfEdge::what() const noexcept
    {
        return "Error: Attempt to create edge to one vertex.";
    }

    const char *mtm::InvalidEdgeVertex::what() const noexcept
    {
        return "Error: Invalid edge vertex.";
    }

    const char *mtm::DuplicateEdge::what() const noexcept
    {
        return "Error: Duplicate edge attempt.";
    }
    const char *mtm::IllegalCommand::what() const noexcept
    {
        return "Error: Invalid command.";
    }

    const char *mtm::UnknownVariable::what() const noexcept
    {
        return "Error: Unknown variable.";
    }
} // namespace mtm
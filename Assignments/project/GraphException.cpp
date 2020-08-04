#include "GraphException.h"

namespace mtm
{
    const char *mtm::IllegalName::what() const noexcept
    {
        return "ERROR: Illegal vertex name.";
    }
    const char *mtm::DuplicateVertex::what() const noexcept
    {
        return "ERROR: Duplicate vertex name.";
    }

    const char *mtm::SelfEdge::what() const noexcept
    {
        return "ERROR: Attempt to create edge to one vertex.";
    }

    const char *mtm::InvalidEdgeVertex::what() const noexcept
    {
        return "ERROR: Invalid edge vertex.";
    }

    const char *mtm::DuplicateEdge::what() const noexcept
    {
        return "ERROR: Duplicate edge attempt.";
    }
} // namespace mtm
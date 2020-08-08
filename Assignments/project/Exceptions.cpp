#include "Exceptions.h"
namespace mtm
{
    mtm::IllegalName::IllegalName(const std::string vertex) : error("Error: Illegal vertex name '" + vertex + "'")
    {
    }
    const char* mtm::IllegalName::what() const noexcept
    {
        return error.c_str();
    }

    mtm::DuplicateVertex::DuplicateVertex(const std::string vertex) : error("Error: Duplicate vertex name '" + vertex + "'")
    {
    }
    const char* mtm::DuplicateVertex::what() const noexcept
    {
        return error.c_str();
    }

    mtm::SelfEdge::SelfEdge(const std::string vertex) : error("Error: Attempt to create edge to same vertex '" + vertex + "'")
    {
    }
    const char* mtm::SelfEdge::what() const noexcept
    {
        return error.c_str();
    }

    mtm::InvalidEdgeVertex::InvalidEdgeVertex(const std::string vertex) : error("Error: Invalid edge vertex '" + vertex + "'")
    {
    }
    const char* mtm::InvalidEdgeVertex::what() const noexcept
    {
        return error.c_str();
    }

    mtm::DuplicateEdge::DuplicateEdge(const std::string edge) : error("Error: Attempted to create a duplicate edge '" + edge + "'")
    {
    }
    const char* mtm::DuplicateEdge::what() const noexcept
    {
        return error.c_str();
    }

    mtm::IllegalCommand::IllegalCommand(const std::string command) : error("Error: Unrecognized command '" + command + "'")
    {
    }
    const char* mtm::IllegalCommand::what() const noexcept
    {
        return error.c_str();
    }

    mtm::UnknownVariable::UnknownVariable(const std::string variable) : error("Error: Undefined variable '" + variable + "'")
    {
    }
    const char* mtm::UnknownVariable::what() const noexcept
    {
        return error.c_str();
    }
}
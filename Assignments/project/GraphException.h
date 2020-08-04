#ifndef GRAPH_EXCEPTION_H
#define GRAPH_EXCEPTION_H

#include <exception>

namespace mtm
{
    class GraphException : public std::exception
    {
    public:
        GraphException() = default;
        ~GraphException() = default;
    };

    class Exception : public GraphException
    {
    };

    class IllegalName : public Exception
    {
    public:
        const char *what() const noexcept;
    };

    class DuplicateVertex : public Exception
    {
    public:
        const char *what() const noexcept;
    };
    class SelfEdge : public Exception
    {
    public:
        const char *what() const noexcept;
    };
    class InvalidEdgeVertex : public Exception
    {
    public:
        const char *what() const noexcept;
    };

    class DuplicateEdge : public Exception
    {
    public:
        const char *what() const noexcept;
    };
}; // namespace mtm

#endif
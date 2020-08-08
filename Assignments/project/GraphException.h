#ifndef GRAPH_EXCEPTION_H
#define GRAPH_EXCEPTION_H

#include <exception>
#include <string>

namespace mtm
{
    class Exception : public std::exception
    {
    };

    class GraphException : public Exception
    {
    private:
        std::string error;
    public:
        GraphException(std::string error) :error(error)
        {
        }
        virtual const char *what() const noexcept override;
    };

    class IllegalName : public GraphException
    {
        
    public:
        IllegalName(std::string name) : GraphException("Error: Illegal vertex name '" + name + "'")
        {
        }
        const char *what() const noexcept override;
    };

    class DuplicateVertex : public GraphException
    {
    public:
        const char *what() const noexcept override;
    };
    class SelfEdge : public GraphException
    {
    public:
        const char *what() const noexcept override;
    };
    class InvalidEdgeVertex : public GraphException
    {
    public:
        const char *what() const noexcept override;
    };

    class DuplicateEdge : public GraphException
    {
    public:
        const char *what() const noexcept override;
    };

    class IllegalCommand : public GraphException
    {
    public:
        const char *what() const noexcept override;
    };

    class UnknownVariable : public GraphException
    {
    public:
        const char *what() const noexcept override;
    };

} // namespace mtm

#endif
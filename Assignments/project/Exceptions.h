#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>
#include <string>

namespace mtm
{
    class Exception : public std::exception
    {
    };

    class IllegalName : public Exception
    {
    private:
        std::string error;
    public:
        IllegalName(const std::string vertex);
        const char* what() const noexcept override;
    };

    class DuplicateVertex : public Exception
    {
    private:
        std::string error;
    public:
        DuplicateVertex(const std::string vertex);
        const char* what() const noexcept override;
    };

    class SelfEdge : public Exception
    {
    private:
        std::string error;
    public:
        SelfEdge(const std::string vertex);
        const char* what() const noexcept override;
    };

    class InvalidEdgeVertex : public Exception
    {
    private:
        std::string error;
    public:
        InvalidEdgeVertex(const std::string vertex);
        const char* what() const noexcept override;
    };

    class DuplicateEdge : public Exception
    {
    private:
        std::string error;
    public:
        DuplicateEdge(const std::string vertex);
        const char* what() const noexcept override;
    };

    class IllegalCommand : public Exception
    {
    private:
        std::string error;
    public:
        IllegalCommand(const std::string vertex);
        const char* what() const noexcept override;
    };

    class UnknownVariable : public Exception
    {
    private:
        std::string error;
    public:
        UnknownVariable(const std::string vertex);
        const char* what() const noexcept override;
    };
}

#endif
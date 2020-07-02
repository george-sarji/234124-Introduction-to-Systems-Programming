#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>

namespace mtm
{
    class Exception : public std::exception
    {
    public:
        Exception() = default;
        ~Exception() = default;
    };

    class GameException : public Exception
    {
    public:
        GameException() = default;
        ~GameException() = default;
    };

    class IllegalArgument : public GameException
    {
    public:
        IllegalArgument() = default;
        ~IllegalArgument() = default;
        const char *what() const noexcept;
    };
    class IllegalCell : public GameException
    {
    public:
        IllegalCell() = default;
        ~IllegalCell() = default;
        const char *what() const noexcept;
    };
    class CellEmpty : public GameException
    {
    public:
        CellEmpty() = default;
        ~CellEmpty() = default;
        const char *what() const noexcept;
    };
    class MoveTooFar : public GameException
    {
    public:
        MoveTooFar() = default;
        ~MoveTooFar() = default;
        const char *what() const noexcept;
    };
    class CellOccupied : public GameException
    {
    public:
        CellOccupied() = default;
        ~CellOccupied() = default;
        const char *what() const noexcept;
    };
    class OutOfRange : public GameException
    {
    public:
        OutOfRange() = default;
        ~OutOfRange() = default;
        const char *what() const noexcept;
    };
    class OutOfAmmo : public GameException
    {
    public:
        OutOfAmmo() = default;
        ~OutOfAmmo() = default;
        const char *what() const noexcept;
    };
    class IllegalTarget : public GameException
    {
    public:
        IllegalTarget() = default;
        ~IllegalTarget() = default;
        const char *what() const noexcept;
    };

} // namespace mtm
#endif
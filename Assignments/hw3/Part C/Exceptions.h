#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include <exception>

namespace mtm{
    class Exception : public std::exception{};

    class GameException : public Exception{};

    class IllegalArgument : public GameException{
        const char* what() noexcept;
    };
    class IllegalCell : public GameException{
        const char* what() noexcept;
    };
    class CellEmpty : public GameException{
        const char* what() noexcept;
    };
    class MoveTooFar : public GameException{
        const char* what() noexcept;
    };
    class CellOccupied : public GameException{
        const char* what() noexcept;
    };
    class OutOfRange : public GameException{
        const char* what() noexcept;
    };
    class OutOfAmmo : public GameException{
        const char* what() noexcept;
    };
    class IllegalTarget : public GameException{
        const char* what() noexcept;
    };

}
#endif
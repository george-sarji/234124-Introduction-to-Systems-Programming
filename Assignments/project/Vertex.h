#ifndef VERTEX_H
#define VERTEX_H

#include <string>

namespace mtm
{
    class Vertex
    {
    private:
        std::string name;

    public:
        Vertex(std::string name);
        ~Vertex() = default;
        std::string getName();
        static bool isNameValid(std::string name);
    }
} // namespace mtm

#endif
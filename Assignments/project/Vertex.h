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
        void operator=(const Vertex &v);
        bool operator==(const Vertex &v) const;
    };
}; // namespace mtm

#endif
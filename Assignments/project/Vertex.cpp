#include "Vertex.h"
#include "GraphException.h"
#include <algorithm>

namespace mtm
{
    mtm::Vertex::Vertex(std::string name) : name(name) {}

    bool mtm::Vertex::isNameValid(std::string name)
    {
        // Iterate through the name itself.
        int openingBrackets = 0;
        for (auto iterator = name.begin(); iterator != name.end(); ++iterator)
        {
            if (!isalpha(*iterator) && !isdigit(*iterator) && *iterator != '[' && *iterator != ']' && *iterator != ';')
            {
                throw IllegalName();
            }
            // Check if the current letter is an opening bracket.
            if (*iterator == '[')
                openingBrackets++;
            if (*iterator == ']')
                openingBrackets--;

            // Check if current letter is a semi-colon.
            if (*iterator == ';')
            {
                // Make sure we have a valid opening bracket.
                if (openingBrackets <= 0)
                {
                    // No valid opening bracket.
                    throw mtm::IllegalName();
                }
            }

            // Check the status of the counter.
            if (openingBrackets < 0)
            {
                // Extra closing bracket.
                throw mtm::IllegalName();
            }
        }
        // Check if we still have an open bracket.
        if (openingBrackets > 0)
        {
            throw mtm::IllegalName();
        }
        return true;
    }
    std::string mtm::Vertex::getName() const
    {
        return name;
    }

    bool mtm::Vertex::operator==(const mtm::Vertex &v) const
    {
        return v.name == name;
    }

    void mtm::Vertex::operator=(const mtm::Vertex &v)
    {
        // Set the current name to the given name.
        name = v.name;
    }

    bool mtm::Vertex::operator<(const Vertex &v) const
    {
        return name < v.name;
    }

} // namespace mtm

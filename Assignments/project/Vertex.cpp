#include "Vertex.h"

namespace mtm
{
    mtm::Vertex::Vertex(std::string name) : name(name) {}

    bool mtm::Vertex::isNameValid(std::string name)
    {
        // TODO: Name validation.
        // Iterate through the name itself.
        int openingBrackets = 0;
        for (auto iterator = name.begin(); iterator != name.end(); ++iterator)
        {
            if ((*iterator < 'A' || *iterator > 'Z') &&
                    (*iterator < 'a' || *iterator > 'z') ||
                (*iterator < '0' || *iterator > '9'))
            {
                printf("ERROR: Invalid character in string.");
                return false;
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
                    printf("ERROR: Invalid semi-colon in name.");
                    return false;
                }
            }

            // Check the status of the counter.
            if (openingBrackets < 0)
            {
                // Extra closing bracket.
                printf("ERROR: Invalid closing bracket.");
                return false;
            }
        }
        // Check if we still have an open bracket.
        if (openingBrackets > 0)
        {
            printf("ERROR: Invalid opening bracket.");
            return false;
        }
        return true;
    }
} // namespace mtm
#include "Graph.h"

#include <string>
#include "Vertex.h"

namespace mtm
{
    mtm::Graph::Graph() : vertices(), edges() {}

    void mtm::Graph::addVertex(std::string identifier)
    {
        // Check if the identifier is valid.
        if (!mtm::Vertex::isNameValid(identifier))
        {
            return;
        }
        // Valid identifier. Check if it's a duplicate.
        for (auto iterator = vertices.begin(); iterator != vertices.end(); ++iterator)
        {
            if (iterator->getName() == identifier)
            {
                // Same name. Exit.
                printf("ERROR: Duplicate vertex entry.");
                return;
            }
        }
        // No duplicate names. Good to assign.
        mtm::Vertex vertex(identifier);
        vertices.push_back(vertex);
    }

    void mtm::Graph::removeVertex(std::string identifier)
    {
        // Search for the given vertex.
        for (auto iterator = vertices.begin(); iterator != vertices.end(); ++iterator)
        {
            if (iterator->getName() == identifier)
            {
                // Successful hit. Remove this vertex.
                vertices.erase(iterator);
                // Go through the edges list and remove the relevant edges.
                auto edgeIterator = edges.begin();
                while (edgeIterator != edges.end())
                {

                    // Check if the identifier is relevant.
                    if (edgeIterator->getDestination().getName() == identifier || edgeIterator->getOrigin().getName() == identifier)
                    {
                        // Remove this edge.
                        edgeIterator = edges.erase(edgeIterator);
                    }
                    else
                    {
                        ++edgeIterator;
                    }
                }
                return;
            }
        }
    }
} // namespace mtm
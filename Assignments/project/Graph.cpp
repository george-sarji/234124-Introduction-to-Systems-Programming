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

    void mtm::Graph::addEdge(std::string originId, std::string destinationId)
    {
        // Check if we are doing a loop.
        if (originId == destinationId)
        {
            printf("ERROR: Attempt of edge creation to same vertex.");
            return;
        }
        // Check if we can find any of the identifiers inside the vertices.
        mtm::Vertex origin = NULL, destination = NULL;
        bool originFlag = false, destinationFlag = false;
        for (auto iterator = vertices.begin(); iterator != vertices.end(); ++iterator)
        {
            if (iterator->getName() == originId)
            {
                origin = *iterator;
                originFlag = true;
            }
            if (iterator->getName() == destinationId)
            {
                destination = *iterator;
                destinationFlag = true;
            }

            if (destinationFlag && originFlag)
            {
                break;
            }
        }

        if (!destinationFlag || !originFlag)
        {
            printf("ERROR: Attempt of edge creation to invalid vertices.");
            return;
        }
        // Create a new edge.
        mtm::Edge edge(origin, destination);
        // Push the edge into the vector.
        edges.push_back(edge);
    }

    void mtm::Graph::removeEdge(std::string originId, std::string destinationId)
    {
        auto iterator = edges.begin();
        while (iterator != edges.end())
        {
            // Check if origin and destination match.
            if (iterator->getDestination().getName() == destinationId && iterator->getOrigin().getName() == originId)
            {
                // Positive hit. Remove the iterator and exit.
                edges.erase(iterator);
                return;
            }
            ++iterator;
        }
    }

    mtm::Graph mtm::Graph::operator+(Graph& graph) {
        // TODO
    }
    mtm::Graph mtm::Graph::operator^(Graph& graph) {
        // TODO
    }
    mtm::Graph mtm::Graph::operator-(Graph& graph) {
        // TODO
    }
    mtm::Graph mtm::Graph::operator*(Graph& graph) {
        // TODO
    }

} // namespace mtm
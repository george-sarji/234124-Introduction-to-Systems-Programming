#include "Graph.h"
#include "GraphException.h"
#include <string>
#include "Vertex.h"

namespace mtm
{
    mtm::Graph::Graph() : vertices(), edges() {}

    mtm::Graph::Graph(const Graph &graph)
    {
    }

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
                throw DuplicateVertex();
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
        // We need to search for the given vertices.
        // Check if we are creating an edge from and to the same point.
        if (originId == destinationId)
        {
            throw SelfEdge();
        }
        // Go through the current vertices and retrieve them.
        mtm::Vertex *origin = nullptr, *destination = nullptr;
        auto it = vertices.begin();
        while (it != vertices.end())
        {
            // Check the current item.
            if (it->getName() == originId)
            {
                origin = &*it;
            }
            else if (it->getName() == destinationId)
            {
                destination = &*it;
            }
            ++it;
        }

        // Check if we have a valid origin and destination.
        if (origin == nullptr || destination == nullptr)
        {
            throw InvalidEdgeVertex();
        }
        // Double check the edges, make sure not a duplicate.
        for (auto it = edges.begin(); it != edges.end(); ++it)
        {
            if (it->getOrigin() == *origin && it->getDestination() == *destination)
            {
                // Duplicate edge.
                throw DuplicateEdge();
            }
        }
        // Create an edge according to the two vertices.
        mtm::Edge edge(*origin, *destination);
        // Push the current edge.
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

    mtm::Graph mtm::Graph::operator+(Graph &graph)
    {
        // TODO
        // Union removes duplicates and only stores one item.
        return *this;
    }
    mtm::Graph mtm::Graph::operator^(Graph &graph)
    {
        // TODO
        return *this;
    }
    mtm::Graph mtm::Graph::operator-(Graph &graph)
    {
        // TODO
        return *this;
    }
    mtm::Graph mtm::Graph::operator*(Graph &graph)
    {
        // TODO
        return *this;
    }

} // namespace mtm
#include "Graph.h"
#include "GraphException.h"
#include <string>
#include <algorithm>
#include <iostream>

namespace mtm
{
    mtm::Graph::Graph() : vertices(), edges() {}

    mtm::Graph::Graph(const Graph &graph)
    {
    }
    mtm::Graph::~Graph() {}

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

    bool mtm::Graph::isContainsVertex(const mtm::Vertex &vertex) const
    {
        // Go through the vertices that we have.
        for (auto it = vertices.begin(); it != vertices.end(); ++it)
        {
            if (*it == vertex)
            {
                // We have the same vertex.
                return true;
            }
        }
        return false;
    }

    bool mtm::Graph::isContainsEdge(const mtm::Edge &edge) const
    {
        for (auto it = edges.begin(); it != edges.end(); ++it)
        {
            if (*it == edge)
            {
                // We have the same edge.
                return true;
            }
        }
        return false;
    }

    mtm::Graph mtm::Graph::complement() const
    {
        // Create a new graph.
        Graph newGraph;
        // Add the same vertices.
        for (auto it = vertices.begin(); it != vertices.end(); ++it)
        {
            newGraph.addVertex(it->getName());
        }
        // Go through the vertices.
        for (auto it = vertices.begin(); it != vertices.end(); ++it)
        {
            // Check with all the other vertices if the edge is contained.
            for (auto init = vertices.begin(); init != vertices.end(); ++init)
            {
                // Check if same iterator standpoint.
                if (init == it)
                    continue;
                // Create a new edge.
                mtm::Edge current(it->getName(), init->getName());
                // Check if it's contained in the graph.
                if (!isContainsEdge(current))
                {
                    newGraph.edges.push_back(current);
                }
            }
        }
        return newGraph;
    }

    mtm::Graph mtm::Graph::operator+(Graph &graph)
    {
        // Union removes duplicates and only stores one item.
        // Go through the vertices and add them into a new graph.
        Graph newGraph;
        for (auto it = vertices.begin(); it != vertices.end(); ++it)
        {
            // Add the current vertex to the new graph.
            try
            {
                newGraph.addVertex(it->getName());
            }
            catch (const mtm::GraphException &e)
            {
                continue;
            }
        }
        // Add the second graph.
        for (auto it = graph.vertices.begin(); it != graph.vertices.end(); ++it)
        {
            // Add the current vertex to the new graph.
            try
            {
                newGraph.addVertex(it->getName());
            }
            catch (const mtm::GraphException &e)
            {
                continue;
            }
        }

        // Go ahead and add the edges.
        for (auto it = edges.begin(); it != edges.end(); ++it)
        {
            try
            {
                newGraph.addEdge(it->getOrigin().getName(), it->getDestination().getName());
            }
            catch (const mtm::GraphException &e)
            {
                continue;
            }
        }
        for (auto it = graph.edges.begin(); it != graph.edges.end(); ++it)
        {
            try
            {
                newGraph.addEdge(it->getOrigin().getName(), it->getDestination().getName());
            }
            catch (const mtm::GraphException &e)
            {
                continue;
            }
        }
        return newGraph;
    }
    mtm::Graph mtm::Graph::operator^(Graph &graph)
    {
        // Create a new graph
        Graph newGraph;
        // Go through the current graph and add the overlapping edges and vertices.
        for (auto it = vertices.begin(); it != vertices.end(); ++it)
        {
            // Check if the current vertex is also contained in the other graph.
            if (graph.isContainsVertex(*it))
            {
                // Add the vertex to the new graph.
                newGraph.addVertex(it->getName());
            }
        }
        for (auto it = edges.begin(); it != edges.end(); ++it)
        {
            if (graph.isContainsEdge(*it))
            {
                newGraph.addEdge(it->getOrigin().getName(), it->getDestination().getName());
            }
        }
        return newGraph;
    }
    mtm::Graph mtm::Graph::operator-(Graph &graph)
    {
        // Create a new graph.
        Graph newGraph;
        // Go through the vertices.
        for (auto it = vertices.begin(); it != vertices.end(); ++it)
        {
            if (!graph.isContainsVertex(*it))
            {
                // Not contained. Add to the new graph.
                newGraph.addVertex(it->getName());
            }
        }
        // Go through the edges.
        for (auto it = edges.begin(); it != edges.end(); ++it)
        {
            if (!graph.isContainsEdge(*it))
            {
                newGraph.addEdge(it->getOrigin().getName(), it->getDestination().getName());
            }
        }
        return newGraph;
    }
    mtm::Graph mtm::Graph::operator*(Graph &graph)
    {
        Graph newGraph;
        for (auto it = vertices.begin(); it != vertices.end(); ++it)
        {
            for (auto init = graph.vertices.begin(); init != graph.vertices.end(); ++init)
            {
                // Add the current vertex with the new name.
                newGraph.addVertex("[" + it->getName() + ";" + init->getName() + "]");
            }
        }
        for (auto it = edges.begin(); it != edges.end(); ++it)
        {
            for (auto init = graph.edges.begin(); init != graph.edges.end(); ++init)
            {
                // Add the current edge.
                std::string origin = "[" + it->getOrigin().getName() + ";" + init->getOrigin().getName() + "]";
                std::string destination = "[" + it->getDestination().getName() + ";" + init->getDestination().getName() + "]";
                newGraph.addEdge(origin, destination);
            }
        }
        return newGraph;
    }
    std::ostream &operator<<(std::ostream &stream, Graph &graph)
    {
        // Sort the vertices and the edges.
        std::sort(graph.edges.begin(), graph.edges.end());
        std::sort(graph.vertices.begin(), graph.vertices.end());
        // Go through the vertices.
        for (auto it = graph.vertices.begin(); it != graph.vertices.end(); ++it)
        {
            // Add to the stream with a new line.
            stream << it->getName() << std::endl;
        }
        // Check if we have any edges.
        if (graph.edges.size() != 0)
        {
            // Print the spacer.
            stream << "$" << std::endl;
        }
        for (auto it = graph.edges.begin(); it != graph.edges.end(); ++it)
        {
            stream << it->getOrigin().getName() << " " << it->getDestination().getName() << std::endl;
        }
        return stream;
    }

    mtm::Graph create() {
        Graph graph;
        return graph;
    }
    void destroy(mtm::Graph graph) {
        graph.~Graph();
    }
} // namespace mtm
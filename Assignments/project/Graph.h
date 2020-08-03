#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include "Edge.h"
#include "Vertex.h"

namespace mtm
{
    class Graph
    {
    private:
        std::vector<mtm::Vertex> vertices;
        std::vector<mtm::Edge> edges;

    public:
        Graph();
        ~Graph() = default;
        void addVertex(std::string identifier);
        void removeVertex(std::string identifier);
        void addEdge(std::string originId, std::string destinationId);
        void removeEdge(std::string originId, std::string destinationId);

        // ! Operator overloads
        // TODO: Union operator overload
        Graph operator+(Graph &graph);
        // TODO: Intersection operator overload
        Graph operator^(Graph &graph);
        // TODO: Difference operator overload
        Graph operator-(Graph &graph);
        // TODO: Product operator overload
        Graph operator*(Graph &graph);
        // TODO: Complement operator overload
    };

}; // namespace mtm

#endif
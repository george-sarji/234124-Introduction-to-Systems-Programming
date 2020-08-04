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
        Graph(const Graph &graph);
        ~Graph() = default;
        void addVertex(std::string identifier);
        void removeVertex(std::string identifier);
        void addEdge(std::string originId, std::string destinationId);
        void removeEdge(std::string originId, std::string destinationId);
        bool isContainsVertex(const mtm::Vertex &vertex);
        bool isContainsEdge(const mtm::Edge &edge);

        // ! Operator overloads
        Graph operator+(Graph &graph);
        Graph operator^(Graph &graph);
        Graph operator-(Graph &graph);
        Graph operator*(Graph &graph);
        // TODO: Complement operator overload
    };

}; // namespace mtm

#endif
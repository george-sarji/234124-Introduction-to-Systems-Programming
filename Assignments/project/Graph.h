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
        ~Graph();
        void addVertex(std::string identifier);
        void removeVertex(std::string identifier);
        void addEdge(std::string originId, std::string destinationId);
        void removeEdge(std::string originId, std::string destinationId);
    }

} // namespace mtm

#endif
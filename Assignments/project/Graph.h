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
    }

} // namespace mtm

#endif
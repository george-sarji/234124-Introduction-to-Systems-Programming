#ifndef EDGE_H
#define EDGE_H

#include <vector>
#include "Vertex.h"

namespace mtm
{
    class Edge
    {
    private:
        std::pair<mtm::Vertex, mtm::Vertex> edge;

    public:
        Edge(mtm::Vertex origin, mtm::Vertex destination);
        ~Edge() = default;
        mtm::Vertex getDestination() const;
        mtm::Vertex getOrigin() const;

        bool operator==(const Edge &edge) const;

        bool operator<(const Edge& edge) const;
    };
} // namespace mtm

#endif
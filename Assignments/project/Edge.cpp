#include "Graph.h"
#include "Edge.h"
#include <vector>

namespace mtm
{
    mtm::Edge::Edge(mtm::Vertex origin, mtm::Vertex destination) : edge(origin, destination) {}

    mtm::Vertex mtm::Edge::getOrigin() const
    {
        return edge.first;
    }

    mtm::Vertex mtm::Edge::getDestination() const
    {
        return edge.second;
    }

    bool mtm::Edge::operator==(const mtm::Edge &e) const
    {
        return edge.first == e.edge.first && edge.second == e.edge.second;
    }

} // namespace mtm
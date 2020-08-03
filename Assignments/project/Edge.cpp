#include "Graph.h"
#include "Edge.h"
#include <vector>

namespace mtm
{
    mtm::Edge::Edge(mtm::Vertex origin, mtm::Vertex destination) : edge(origin, destination) {}

    mtm::Vertex mtm::Edge::getOrigin()
    {
        return edge.first;
    }

    mtm::Vertex mtm::Edge::getDestination()
    {
        return edge.second;
    }

} // namespace mtm
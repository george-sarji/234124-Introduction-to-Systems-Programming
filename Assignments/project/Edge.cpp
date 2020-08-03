#include "Graph.h"
#include "Edge.h"
#include <vector>

namespace mtm
{
    mtm::Edge::Edge(mtm::Vertex origin, mtm::Vertex destination)
    {
        // Allocate a new pair.
        this->edge = std::pair(origin, destination);
    }

    mtm::Vertex mtm::Edge::getOrigin()
    {
        return edge.first;
    }

    mtm::Vertex mtm::Edge::getDestination()
    {
        return edge.second;
    }

} // namespace mtm
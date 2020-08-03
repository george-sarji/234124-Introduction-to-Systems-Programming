#ifndef EDGE_H
#define EDGE_H

#include <vector>
#include "Vertex.h"

namespace mtm
{
    class Edge
    {
        std::vector<mtm::Vertex> connections;
    }
} // namespace mtm

#endif
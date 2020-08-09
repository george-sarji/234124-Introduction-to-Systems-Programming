#ifndef GRAPH_WRAPPER_H
#define GRAPH_WRAPPER_H
#include "Graph.h"
#include <string>

namespace wrapper
{
    mtm::Graph createGraph();
    void destroyGraph(mtm::Graph* graph);
    mtm::Graph* addVertex(mtm::Graph* g, std::string v);
    mtm::Graph* addEdge(mtm::Graph* g, std::string origin, std::string destination);
    void displayGraph(mtm::Graph* g);

    mtm::Graph* graphUnion(mtm::Graph* g1, mtm::Graph* g2, mtm::Graph* out);
    mtm::Graph* graphIntersection(mtm::Graph* g1, mtm::Graph* g2, mtm::Graph* out);
    mtm::Graph* GraphDifference(mtm::Graph* g1, mtm::Graph* g2, mtm::Graph* out);
    mtm::Graph* graphProduct(mtm::Graph* g1, mtm::Graph* g2, mtm::Graph* out);
    mtm::Graph* graphComplement(mtm::Graph* in, mtm::Graph* out);
}

#endif
#ifndef GRAPH_WRAPPER_H
#define GRAPH_WRAPPER_H
#include "Graph.h"
#include <string>

mtm::Graph *create();
void destroy(mtm::Graph*);
mtm::Graph* addVertex(mtm::Graph*, const char*);
mtm::Graph* addEdge(mtm::Graph*, const char*, const char*);
void disp(mtm::Graph*);

mtm::Graph* graphUnion(mtm::Graph*, mtm::Graph*, mtm::Graph*);
mtm::Graph* graphIntersection(mtm::Graph*, mtm::Graph*, mtm::Graph*);
mtm::Graph* GraphDifference(mtm::Graph*, mtm::Graph*, mtm::Graph*);
mtm::Graph* graphProduct(mtm::Graph*, mtm::Graph*, mtm::Graph*);
mtm::Graph* graphComplement(mtm::Graph*, mtm::Graph*);

#endif
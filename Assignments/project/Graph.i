%module Graph
%include "Graph.h"
%{
    #include "Graph.h"
    %}
Graph create();
void destroy(mtm::Graph graph);
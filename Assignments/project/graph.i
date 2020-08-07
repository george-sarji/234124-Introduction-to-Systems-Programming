%module graph
%include "std_vector.i"
%include "std_string.i"
%{
    #include "Graph.h"
    #include "Edge.h"
    #include "Vertex.h"
    #include "GraphException.h"
    %}

%template(StringVector)std::vector<std::string>;
%rename(__repr__) operator<<;
%rename(__add__) operator+;
%rename(__del__) ~Graph;
%include "Graph.h"

%extend mtm::Graph{
    Graph add(Graph& g) {
    g = g+*$self;
    return g;
}
}
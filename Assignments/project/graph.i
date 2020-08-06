%module graph
%include "std_vector.i"
%include "std_string.i"
%{
#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"
#include "GraphException.h"
%}

%template(StringVector) std::vector<std::string>;
%rename(display) operator<<;
%include "Graph.h"
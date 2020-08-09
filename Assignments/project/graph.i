%module graph_wrap
%include "std_string.i"
%include "typemaps.i"
%{
    #include "Graph.h"
    #include "Edge.h"
    #include "Vertex.h"
    #include "Exceptions.h"
    #include "GraphWrapper.h"
    %}

%rename(__str__) operator<<;
%rename(complement) operator!;

%include "GraphWrapper.h"
%include "Graph.h"
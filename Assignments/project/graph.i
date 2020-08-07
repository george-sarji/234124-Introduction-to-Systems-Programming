%module graph
%include "std_vector.i"
%include "std_string.i"
%include "typemaps.i"
%{
    #include "Graph.h"
    #include "Edge.h"
    #include "Vertex.h"
    #include "GraphException.h"
    using namespace mtm;
    %}

%template(StringVector)std::vector<std::string>;
%rename(__add__) Graph::operator+;
%rename(__sub__) Graph::operator-;
%rename(__mul__) Graph::operator*;
%rename(__xor__) Graph::operator^;
%rename(comp) Graph::operator!;
// %rename(__invert__) Graph::operator!;
// %rename(__str__) Graph::toString;

%exception {
  try {
    $action
  }
  catch (const Exception &e) {
    std::cout << e.what() << std::endl;
  }
}


%include "Graph.h"
%module Graph
%include "Graph.h"
%{
    #include "Graph.h"
    %}
class Graph
{

public:
    Graph();
    Graph(const Graph &graph);
    ~Graph() = default;
    void addVertex(std::string identifier);
    void removeVertex(std::string identifier);
    void addEdge(std::string originId, std::string destinationId);
    void removeEdge(std::string originId, std::string destinationId);
    bool isContainsVertex(const mtm::Vertex &vertex) const;
    bool isContainsEdge(const mtm::Edge &edge) const;

    Graph complement() const;

    // ! Operator overloads
    Graph operator+(Graph &graph);
    Graph operator^(Graph &graph);
    Graph operator-(Graph &graph);
    Graph operator*(Graph &graph);
    friend std::ostream &operator<<(std::ostream &stream, Graph &graph);
}

Graph create();
void destroy(mtm::Graph graph);

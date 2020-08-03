#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include <string>
namespace mtm
{

    class Graph
    {
    private:
        std::map<std::string, std::vector<std::string>> edges;
        std::vector<std::string> vertices;

    public:
        Graph() = default;
        ~Graph() = default;
        std::map<std::string, std::vector<std::string>> getEdges();
        std::vector<std::string> getVertices();
        void addVertex(std::string vertexName);
        void removeVertex(std::string vertexName);
        void addEdge(std::string to, std::string from);
        void removeEdge(std::string to, std::string from);
    };
}; // namespace mtm

#endif
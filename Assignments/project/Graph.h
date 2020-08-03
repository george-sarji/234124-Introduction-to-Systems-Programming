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
        std::map<std::string, std::string> links;
        std::vector<std::string> points;

    public:
        std::map<std::string, std::string> getLinks();
        std::vector<std::string> getPoints();
    };
}; // namespace mtm

#endif
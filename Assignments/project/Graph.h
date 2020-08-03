#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <map>
#include <string>
#include <std>
namespace mtm
{

    class Graph
    {
    private:
        std::vector<std::map<std::string, std::string>> links;
        std::set<std::string> points;

    public:
        Graph();
        std::vector<std::map<std::string, std::string>> getLinks();
        std::set<std::string> getPoints();
        void addGraphPoint(std::string pointName);
        void removeGraphPoint(std::string pointName);
        void addLink(std::string to, std::string from);
        void removeLink(std::string to, std::string from);
    };
}; // namespace mtm

#endif
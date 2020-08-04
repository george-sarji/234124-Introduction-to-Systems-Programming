#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"
#include "GraphException.h"
#include <iostream>

using namespace mtm;

void test1()
{
    Graph graph;
    try
    {
        graph.addVertex("test");
    }
    catch (const mtm::GraphException &e)
    {
        std::cout << e.what() << std::endl;
    }
    try
    {
        graph.addVertex("test1");
    }
    catch (const mtm::GraphException &e)
    {
        std::cout << e.what() << std::endl;
    }
    graph.addEdge("test", "test1");
    graph.addEdge("test1", "test");

    try
    {
        graph.addEdge("test11", "test1");
        graph.addEdge("test", "test1");
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
    graph.removeVertex("test");
}
int main()
{
    test1();
    return 0;
}

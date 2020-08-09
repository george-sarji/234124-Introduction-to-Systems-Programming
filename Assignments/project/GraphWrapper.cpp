#include "GraphWrapper.h"
#include "Exceptions.h"
#include <iostream>

mtm::Graph *create()
{
    return new mtm::Graph;
}

void destroy(mtm::Graph* g) {
    delete g;
    g = nullptr;
}
mtm::Graph* addVertex(mtm::Graph* graph, const char* vertex)
{
    if(graph == NULL || vertex == NULL) {
        std::cout << "Error: Invalid graph or vertex given." << std::endl;
        return nullptr;
    }
    try
    {
        graph->addVertex(vertex);
        return graph;
    }
    catch (const mtm::Exception& e)
    {
        std::cout << e.what() << std::endl;
    }
    return nullptr;
}
mtm::Graph* addEdge(mtm::Graph* graph, const char* v1, const char* v2)
{
    if(graph == nullptr || v1 == nullptr || v2==nullptr) {
        std::cout << "Error: Invalid graph or vertex given." << std::endl;
        return nullptr;
    }
    try
    {
        graph->addEdge(v1, v2);
        return graph;
    }
    catch (const mtm::Exception& e)
    {
        std::cout << e.what()<<std::endl;
    }
    return nullptr;
}
void disp(mtm::Graph* g)
{
    if(g == nullptr) {
        std::cout << "Error: Invalid graph provided." << std::endl;
        return;
    }
    std::cout << *g <<std::endl;
}


mtm::Graph* graphUnion(mtm::Graph* graph_in1, mtm::Graph* graph_in2, mtm::Graph* graph_out)
{
    if(graph_out == nullptr || graph_in2 == nullptr || graph_in2 == nullptr) {
        std::cout << "Error: Invalid graph given." << std::endl;
        return nullptr;
    }
    try
    {
        // std::cout << graph_in1;
        *graph_out = *graph_in1 + *graph_in2;
    }
    catch (const mtm::Exception& e)
    {
        std::cout << e.what() << std::endl;
        graph_out = nullptr;
    }
    return graph_out;
}
mtm::Graph* graphIntersection(mtm::Graph* graph_in1, mtm::Graph* graph_in2, mtm::Graph* graph_out)
{
    if(graph_out == nullptr || graph_in2 == nullptr || graph_in2 == nullptr) {
        std::cout << "Error: Invalid graph given." << std::endl;
        return nullptr;
    }
    try
    {
        *graph_out = *graph_in1 ^ *graph_in2;
    }
    catch (const mtm::Exception& e)
    {
        std::cout << e.what() << std::endl;
        graph_out = nullptr;
    }
    return graph_out;
}
mtm::Graph* GraphDifference(mtm::Graph* graph_in1, mtm::Graph* graph_in2, mtm::Graph* graph_out)
{
    if(graph_out == nullptr || graph_in2 == nullptr || graph_in2 == nullptr) {
        std::cout << "Error: Invalid graph given." << std::endl;
        return nullptr;
    }
    try
    {
        *graph_out = *graph_in1 - *graph_in2;
    }
    catch (const mtm::Exception& e)
    {
        std::cout << e.what() << std::endl;
        graph_out = nullptr;
    }
    return graph_out;
}
mtm::Graph* graphProduct(mtm::Graph* graph_in1, mtm::Graph* graph_in2, mtm::Graph* graph_out)
{
    if(graph_out == nullptr || graph_in2 == nullptr || graph_in2 == nullptr) {
        std::cout << "Error: Invalid graph given." << std::endl;
        return nullptr;
    }
    try
    {
        *graph_out = *graph_in1 * *graph_in2;
    }
    catch (const mtm::Exception& e)
    {
        std::cout << e.what() << std::endl;
        graph_out = nullptr;
    }
    return graph_out;
}
mtm::Graph* graphComplement(mtm::Graph* graph_in, mtm::Graph* graph_out)
{
    if(graph_in == nullptr || graph_out == nullptr)
    try
    {
        *graph_out = !(*graph_in);
    }
    catch (const mtm::Exception& e)
    {
        std::cout << e.what() << std::endl;
        graph_out = nullptr;
    }
    return graph_out;
}
#include "GraphWrapper.h"
#include "Exceptions.h"
#include <iostream>

namespace wrapper
{
    mtm::Graph createGraph()
    {
        mtm::Graph g;
        return g;
    }
    void destroyGraph(mtm::Graph* graph)
    {
        delete(graph);
    }
    mtm::Graph* addVertex(mtm::Graph* g, std::string v)
    {
        try
        {
            g->addVertex(v);
            return g;
        }
        catch (const mtm::Exception& e)
        {
            std::cout << e.what() << std::endl;
        }
        return nullptr;
    }
    mtm::Graph* addEdge(mtm::Graph* g, std::string origin, std::string destination)
    {
        try
        {
            g->addEdge(origin, destination);
            return g;
        }
        catch (const mtm::Exception& e)
        {
            std::cout << e.what()<<std::endl;
        }
        return nullptr;
    }
    void displayGraph(mtm::Graph* g)
    {
        std::cout << g->toString()<<std::endl;
    }


    mtm::Graph* graphUnion(mtm::Graph* g1, mtm::Graph* g2, mtm::Graph* out)
    {
        try
        {
            *out = *g1 + *g2;
            return out;
        }
        catch (const mtm::Exception& e)
        {
            std::cout << e.what() << std::endl;
        }
        return nullptr;
    }
    mtm::Graph* graphIntersection(mtm::Graph* g1, mtm::Graph* g2, mtm::Graph* out)
    {
        try
        {
            *out = *g1 ^ *g2;
            return out;
        }
        catch (const mtm::Exception& e)
        {
            std::cout << e.what() << std::endl;
        }
        return nullptr;
    }
    mtm::Graph* GraphDifference(mtm::Graph* g1, mtm::Graph* g2, mtm::Graph* out)
    {
        try
        {
            *out = *g1 - *g2;
            return out;
        }
        catch (const mtm::Exception& e)
        {
            std::cout << e.what() << std::endl;
        }
        return nullptr;
    }
    mtm::Graph* graphProduct(mtm::Graph* g1, mtm::Graph* g2, mtm::Graph* out)
    {
        try
        {
            *out = *g1 * *g2;
            return out;
        }
        catch (const mtm::Exception& e)
        {
            std::cout << e.what() << std::endl;
        }
        return nullptr;
    }
    mtm::Graph* graphComplement(mtm::Graph* in, mtm::Graph* out)
    {
        try
        {
            *out = !(*in);
            return out;
        }
        catch (const mtm::Exception& e)
        {
            std::cout << e.what() << std::endl;
        }
        return nullptr;
    }
}
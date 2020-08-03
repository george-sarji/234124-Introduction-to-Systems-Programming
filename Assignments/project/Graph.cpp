#include "Graph.h"
#include <string>
#include <map>

namespace mtm
{
    std::map<std::string, std::vector<std::string>> mtm::Graph::getEdges()
    {
        return this->edges;
    }
    std::vector<std::string> mtm::Graph::getVertices()
    {
        return this->vertices;
    }
    void mtm::Graph::addVertex(std::string vertexName)
    {
        // TODO: Check if it's a valid name.

        // It's a valid name. Carry on.
        // Add the vertex into the list of vertices.
        this->vertices.push_back(vertexName);
        // Create a new vector inside the edges for the vertex.
        // Create a vector for the connections
        std::vector<std::string> edges;
        // Create the map.
        std::pair<std::string, std::vector<std::string>> mapPair(vertexName, edges);
        this->edges.insert(mapPair);
    }

    void mtm::Graph::removeVertex(std::string vertexName)
    {
        // Check if the given vertex name is found within the vertices.
        for (auto iterator = this->vertices.begin(); iterator != this->vertices.end(); ++iterator)
        {
            // Check if the current object is the same as the vertex name.
            if(vertexName == *iterator) {
                // We found the appropriate vertex. We have to remove it.
                this->vertices.erase(iterator);
                // We have to now remove the relevant pair from the map.
                
            }
        }
    }

} // namespace mtm
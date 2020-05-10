#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "map.h"
#include "node.h"

struct Map_t
{
    struct node_t *data;
    struct node_t *iterator;
};

Node mapGetData(Map map)
{
    if (map == NULL)
    {
        return NULL;
    }
    return map->data;
}

void mapSetData(Map map, Node data)
{
    if (map == NULL)
        return;
    map->data = data;
}

Map mapCreate()
{
    // Allocate a new map.
    Map map = malloc(sizeof(*map));
    if (map == NULL)
    {
        return NULL;
    }
    // Allocate new node.
    Node node = nodeCreate();
    if (node == NULL)
    {
        // Free the map.
        free(map);
        return NULL;
    }
    map->data = node;
    return map;
}

void mapDestroy(Map map)
{
    if (map == NULL)
    {
        return;
    }
    // Free the node.
    nodeDestroy(map->data);
    free(map);
}

int mapGetSize(Map map)
{
    if (map == NULL)
    {
        return -1;
    }
    // Go through the data in the map.
    Node current_node = mapGetData(map);
    int counter = 0;
    while (current_node != NULL)
    {
        counter++;
        if (nodeGetNext(current_node) == NULL)
        {
            return counter;
        }
        current_node = nodeGetNext(current_node);
    }
    return counter;
}

bool mapContains(Map map, const char *key)
{
    if (map == NULL)
    {
        return false;
    }
    // Get the nodes.
    Node current_node = mapGetData(map);
    while (current_node != NULL)
    {
        if (nodeGetKey(current_node) == NULL)
        {
            current_node = nodeGetNext(current_node);
            continue;
        }
        else if (strcmp(key, nodeGetKey(current_node)) == 0)
        {
            // Found the key. Return true.
            return true;
        }
        current_node = nodeGetNext(current_node);
    }
    return false;
}

MapResult mapPut(Map map, const char *key, const char *data)
{
    if (map == NULL || key == NULL || data == NULL)
    {
        return MAP_NULL_ARGUMENT;
    }
    // Go through the nodes.
    Node current_node = mapGetData(map);
    // Check if the first node is empty.
    if (current_node == NULL || nodeGetKey(current_node) == NULL)
    {
        // Create a new pair and add it into the node.
        // Allocate new strings.
        if (nodeSetKey(current_node, key) == NULL)
        {
            return MAP_OUT_OF_MEMORY;
        }
        if (nodeSetData(current_node, data) == NULL)
        {
            return MAP_OUT_OF_MEMORY;
        }
        return MAP_SUCCESS;
    }
    while (current_node != NULL)
    {
        if (strcmp(nodeGetKey(current_node), key) == 0)
        {
            // Set the key.
            if (nodeSetKey(current_node, key))
            {
                return MAP_OUT_OF_MEMORY;
            }
            return MAP_SUCCESS;
        }
        else if (nodeGetNext(current_node) == NULL)
        {
            // Last node. Create a new node.
            Node new_node = nodeCreate();
            if (new_node == NULL)
            {
                return MAP_OUT_OF_MEMORY;
            }
            if (nodeSetKey(new_node, key) == NULL || nodeSetData(new_node, data))
            {
                nodeDestroy(new_node);
                return MAP_OUT_OF_MEMORY;
            }
            nodeSetNext(current_node, new_node);
            return MAP_SUCCESS;
        }
        current_node = nodeGetNext(current_node);
    }
    return MAP_ERROR;
}

char *mapGet(Map map, const char *key)
{
    if (map == NULL || key == NULL)
    {
        return NULL;
    }
    // Get the nodes.
    Node current_node = mapGetData(map);
    while (current_node != NULL)
    {
        // Compare.
        if (strcmp(nodeGetKey(current_node), key) == 0)
        {
            // We found the key.
            return nodeGetData(current_node);
        }
        current_node = nodeGetNext(current_node);
    }
    return NULL;
}

MapResult mapRemove(Map map, const char *key)
{
    if (map == NULL || key == NULL)
    {
        return MAP_NULL_ARGUMENT;
    }
    // Go through the nodes.
    Node previous_node = mapGetData(map);
    if (previous_node != NULL && nodeCompareKey(previous_node, key))
    {
        // Remove the data.
        mapSetData(map, nodeGetNext(previous_node));
        nodeDestroy(previous_node);
        return MAP_SUCCESS;
    }
    Node current_node = nodeGetNext(previous_node);
    while (current_node != NULL)
    {
        if (nodeCompareKey(current_node, key))
        {
            // Found the key. Remove the node.
            nodeSetNext(previous_node, nodeGetNext(current_node));
            nodeDestroy(current_node);
            return MAP_SUCCESS;
        }
        previous_node = current_node;
        current_node = nodeGetNext(current_node);
    }
    return MAP_ITEM_DOES_NOT_EXIST;
}

int main()
{
    Map map = mapCreate();
    if (map == NULL)
    {
        return 0;
    }
    int count = 0;
    count = mapGetSize(map);
    printf("%d", count);
    printf("%d", mapContains(map, "012"));
    mapPut(map, "308324772", "John Snow");
    mapPut(map, "208364702", "Sansa Stark");
    mapGet(map, "308324772"); // name = "The Night King"
    mapRemove(map, "208364702");
    mapDestroy(map);
    // mapPut(map, "308324772", "The Night King");
    // name = mapGet(map, "208364702");          // name = "Sansa Stark"
    // bool res = mapContains(map, "108364702"); // res = false
    // if (res)
    //     return 1;
    return 1;
}
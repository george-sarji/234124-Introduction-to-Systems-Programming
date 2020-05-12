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
    map->data = NULL;
    map->iterator = NULL;
    return map;
}

void mapDestroy(Map map)
{
    if (map == NULL)
    {
        return;
    }
    // Free the node.
    map->iterator = NULL;
    Node current_node = mapGetData(map);
    while (current_node != NULL)
    {
        Node next = nodeGetNext(current_node);
        nodeDestroy(current_node);
        current_node = next;
    }
    free(map);
    map = NULL;
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
    if (map == NULL || key == NULL)
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
    if (current_node == NULL)
    {
        // Create a new pair and add it into the node.
        // Allocate new strings.
        // Allocate a new node.
        Node new_node = nodeCreate();
        if (new_node == NULL || nodeSetKey(new_node, key) == NULL || nodeSetData(new_node, data) == NULL)
        {
            return MAP_OUT_OF_MEMORY;
        }
        // Set the data.
        mapSetData(map, new_node);
        return MAP_SUCCESS;
    }
    while (current_node != NULL)
    {
        if (nodeCompareKey(current_node, key))
        {
            // Set the key.
            if (nodeSetData(current_node, data) == NULL)
            {
                return MAP_OUT_OF_MEMORY;
            }
            return MAP_SUCCESS;
        }
        else if (nodeGetNext(current_node) == NULL)
        {
            // Last node. Create a new node.

            Node new_node = nodeSetNext(current_node, nodeCreate());
            if (new_node == NULL || nodeSetKey(new_node, key) == NULL || nodeSetData(new_node, data) == NULL)
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
    while (current_node != NULL && nodeGetKey(current_node) != NULL)
    {
        // Compare.
        if (nodeCompareKey(current_node, key))
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
    // Check the nodes, one by one. We also need the pointer to the previous node.
    Node previous_node = mapGetData(map);
    // Is the first node our hit?
    if (previous_node != NULL && nodeCompareKey(previous_node, key))
    {
        // First node needs to be removed.
        mapSetData(map, nodeGetNext(previous_node));
        nodeDestroy(previous_node);
        return MAP_SUCCESS;
    }
    // Get the second node.
    Node current_node = nodeGetNext(previous_node);
    // Go through the nodes list.
    while (current_node != NULL)
    {
        // Compare the key
        if (nodeCompareKey(current_node, key))
        {
            // We found the node. We have to remove it from the list.
            nodeSetNext(previous_node, nodeGetNext(current_node));
            // Destroy the current node.
            nodeDestroy(current_node);
            // Return.
            return MAP_SUCCESS;
        }
        else
        {
            // Not the key we wanted. Iterate onto the next node.
            previous_node = current_node;
            current_node = nodeGetNext(current_node);
        }
    }
    return MAP_ITEM_DOES_NOT_EXIST;
}

Map mapCopy(Map map)
{
    if (map == NULL)
    {
        return NULL;
    }
    // Create a new map.
    Map new_map = mapCreate();
    if (new_map == NULL)
    {
        return NULL;
    }
    Node original_node = mapGetData(map);
    if (original_node == NULL)
    {
        return new_map;
    }
    Node node_copy = nodeCreate();
    if (node_copy == NULL)
    {
        // Return.
        mapDestroy(new_map);
        return NULL;
    }
    new_map->data = node_copy;
    while (original_node != NULL)
    {
        // Copy the data from the original node to the current node.
        char *key = nodeGetKey(original_node);
        char *data = nodeGetData(original_node);
        nodeSetKey(node_copy, key);
        nodeSetData(node_copy, data);
        if (nodeGetNext(original_node) != NULL)
        {
            // Create a new node as next.
            Node next_node = nodeCreate();
            if (next_node != NULL)
            {
                // Assign it as next.
                nodeSetNext(node_copy, next_node);
            }
            else
            {
                mapDestroy(new_map);
                return NULL;
            }
        }
        node_copy = nodeGetNext(node_copy);
        original_node = nodeGetNext(original_node);
    }
    // mapDestroy(new_map);
    return new_map;
}

MapResult mapClear(Map map)
{
    if (map == NULL)
    {
        return MAP_NULL_ARGUMENT;
    }
    Node current_node = mapGetData(map);
    while (current_node != NULL)
    {
        Node *previous = &current_node;
        current_node = nodeGetNext(current_node);
        nodeDestroy(*previous);
    }
    return MAP_SUCCESS;
}

char *mapGetFirst(Map map)
{
    if (map == NULL || mapGetSize(map) == 0)
    {
        return NULL;
    }
    Node node = mapGetData(map);
    map->iterator = node;
    return nodeGetKey(node);
}

char *mapGetNext(Map map)
{
    // Advance iterator.
    if (map == NULL || map->iterator == NULL || nodeGetNext(map->iterator) == NULL)
    {
        return NULL;
    }
    map->iterator = nodeGetNext(map->iterator);
    return nodeGetKey(map->iterator);
}

// int main()
// {
//     Map map = mapCreate();
//     if (map == NULL)
//     {
//         return 0;
//     }
//     mapPut(map, "308324772", "John Snow");
//     mapPut(map, "208364702", "Sansa Stark");
//     mapGetFirst(map);
//     mapGetNext(map);
//     mapRemove(map, "208364702");
//     mapPut(map, "308324772", "The Night King");
//     char *name = mapGet(map, "208364702"); // name = "Sansa Stark"
//     printf("%s", name);
//     bool res = mapContains(map, "108364702"); // res = false
//     if (res)
//         ;
//     mapDestroy(map);
//     return 1;
// }
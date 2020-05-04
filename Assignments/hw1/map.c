#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "node.h"

struct Map_t
{
    struct node_t *data;
    int iterator;
};

// TODO: mapCreate: Creates new map object - Needs to be tested
Map mapCreate()
{
    Map new_map = malloc(sizeof(Map));
    if (new_map == NULL)
        return NULL;

    // Change iterator status
    new_map->iterator = 0;
    // Allocate new map.
    return new_map;
}

void mapDestroy(Map map)
{
    if (map == NULL)
        return;
    // Go through the linked list
    Node pairs = map->data;
    while (pairs != NULL)
    {
        // Start freeing nodes.
        Node current_pair = pairs;
        pairs = pairs->next;
        free(current_pair->data);
        free(current_pair);
    }
    free(map);
}

// Map mapCopy(Map map)
// {
//     if (map == NULL)
//         return NULL;
// }

// // TODO: mapCopy: Copies map into new one - Needs to be tested
// Map mapCopy(Map map)
// {
//     if (map == NULL)
//         return NULL;
//     //    Allocate new map
//     Map newMap = mapCreate();
//     if (newMap == NULL)
//         return NULL;
//     // Allocate a pair node
//     MapPairNode newPair = malloc(sizeof(MapPairNode));
//     if (newPair == NULL)
//     {
//         mapDestroy(newMap);
//         return NULL;
//     }
//     newMap->pairs = newPair;
//     MapPairNode temp = newPair;
//     MapPairNode current = map->pairs;
//     // Go over the current map pairs.
//     while (current != NULL)
//     {
//         // Copy the key and value
//         temp->data->key = current->data->key;
//         temp->data->value = current->data->value;
//         // Is there a next node?
//         if (current->next != NULL)
//         {
//             // Allocate new temp
//             MapPairNode new = malloc(sizeof(MapPairNode));
//             if (new == NULL)
//             {
//                 // Deallocate everything
//                 mapDestroy(newMap);
//                 return NULL;
//             }
//             temp->next = new;
//         }
//         current = current->next;
//         temp = temp->next;
//     }
//     return newMap;
// }

int mapGetSize(Map map)
{
    if (map == NULL)
        return -1;
    int count = 0;
    Node current_pair = map->data;
    while (current_pair != NULL)
    {
        count++;
        current_pair = current_pair->next;
    }
    return count;
}

bool mapContains(Map map, const char *key)
{
    if (map == NULL || key == NULL)
        return false;
    Node current_pair = map->data;
    while (current_pair != NULL)
    {
        // Check if the current pair's key is equal to the given key.
        if (strcmp(current_pair->data->key, key) == 0)
        {
            // Found the key.
            return true;
        }
        current_pair = current_pair->next;
    }
    // Reached the end without any hits. No matches.
    return false;
}

// TODO: Complete mapPut.
// MapResult mapPut(Map map, const char *key, const char *data)
// {
//     if (map == NULL || key == NULL || data == NULL)
//         return MAP_NULL_ARGUMENT;
//     // Go through the current data in the map.
//     Node current_pair = map->data;
//     while (current_pair != NULL)
//     {
//         // Check if current key matches.
//         if (strcmp(current_pair->data->key, key) == 0)
//         {
//             // We found the matching entry. Update the data.
//             char *copied_str = malloc(strlen(data) * sizeof(char));
//             if (copied_str == NULL)
//                 return MAP_OUT_OF_MEMORY;
//             // Set the copied string.
//             strcpy(copied_str, data);
//             current_pair->data->value = copied_str;
//             return MAP_SUCCESS;
//         }
//         // Check if we are at the last node.
//         else if(current_pair->next == NULL) {
//             // Create a new node and add it and return success.
//             Node new_pair = malloc(sizeof(Node));
//             if(new_pair == NULL) return MAP_OUT_OF_MEMORY;
//             MapPair node_data = malloc(sizeof(MapPair));
//             if(node_data == NULL) return MAP_OUT_OF_MEMORY;
//             // Set the data.
//             char* copied_key = malloc(strlen(key) * sizeof(char));
//             if(copied_key == NULL) return MAP_OUT_OF_MEMORY;
//             strcpy(copied_key, key);
//             node_data->key = copied_key;

//             char* copied_value = malloc(strlen(data)*sizeof(char));
//             if(copied_value==NULL) return MAP_OUT_OF_MEMORY;
//             strcpy(copied_value, data);
//             node_data->value = copied_value;
//             // Assign the values to the node.
//             new_pair->data = node_data;

//             // Set the next to the new node.
//             current_pair->next = new_pair;
//             return MAP_SUCCESS;
//         }
//     }
// }

// // TODO: mapPut: Changes value of key or adds key-value pair
// MapResult mapPut(Map map, const char *key, const char *data)
// {
//     if (map == NULL || key == NULL || data == NULL)
//         return MAP_NULL_ARGUMENT;
//     // Go through the map pairs.
//     MapPairNode pair = map->pairs;
//     while (pair != NULL)
//     {
//         // Check if we can find the key.
//         if (strcmp(pair->data->key, key) == 0)
//         {
//             // Change data of current pair
//             pair->data->value = data;
//             // Return with success
//             return MAP_SUCCESS;
//         }
//         if (pair->next == NULL)
//         {
//             // Last pair. Add and return.
//             // Allocate new pair space
//             MapPairNode newSpace = malloc(sizeof(MapPairNode));
//             if (newSpace == NULL)
//                 return MAP_OUT_OF_MEMORY;
//             // Not null. Allocate data, set into next and return.
//             newSpace->data->key = key;
//             newSpace->data->value = data;
//             pair->next = newSpace;
//             return MAP_SUCCESS;
//         }
//         pair = pair->next;
//     }
//     // Should not be reached.
//     return MAP_ERROR;
// }

char *mapGet(Map map, const char *key)
{
    if (map == NULL || key == NULL)
        return NULL;
    // Get the data.
    Node current_pair = map->data;
    // Iterate over data
    while (current_pair != NULL)
    {
        // Check if current key matches.
        if (strcmp(current_pair->data->key, key) == 0)
        {
            // We found the required entry. Return the data.
            return current_pair->data->value;
        }
    }
    // Returned nothing. Give null.
    return NULL;
}

MapResult mapRemove(Map map, const char *key)
{
    if (map == NULL || key == NULL)
        return MAP_NULL_ARGUMENT;
    // Get the data
    Node current_pair = map->data;
    // Check sidecase: First node is the one we are looking for.
    if (strcmp(current_pair->data->key, key) == 0)
    {
        // We found the key.
        // Remove the element from the list.
        map->data = current_pair->next;
        // Free the current pair.
        free(current_pair->data->key);
        free(current_pair->data->value);
        free(current_pair->data);
        free(current_pair);
        return MAP_SUCCESS;
    }
    // Go through the pairs.
    while (current_pair->next != NULL)
    {
        // Check if the next pair matches.
        Node next_pair = current_pair->next;
        if (strcmp(next_pair->data->key, key) == 0)
        {
            // We found the required node. Skip over.
            current_pair->next = next_pair->next;
            // Free the next pair node
            free(next_pair->data->key);
            free(next_pair->data->value);
            free(next_pair->data);
            free(next_pair);
            return MAP_SUCCESS;
        }
        // Go on to the next node.
        current_pair = current_pair->next;
    }
    // Reached the end, no comparison positives. Return no items in list.
    return MAP_ITEM_DOES_NOT_EXIST;
}

// TODO: mapGetFirst: Retrieves first key in map
char *mapGetFirst(Map map) {}

// TODO: mapGetNext: Retrieves next key in line
char *mapGetNext(Map map) {}

// TODO: mapClear: Clears the map from key-value pairs
MapResult mapClear(Map map) {}
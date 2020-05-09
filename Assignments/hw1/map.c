#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "map.h"
#include "node.h"

struct Map_t
{
    struct node_t *data;
    int iterator;
};

void freeNode(Node node)
{
    // Free only the given node.
    free(node->data->key);
    free(node->data->value);
    free(node->data);
    free(node);
}
void freeNodes(Node node)
{
    // Go through the node's data and free it.
    while (node != NULL)
    {
        Node current = node;
        node = node->next;
        // Free the current node.
        freeNode(current);
    }
}

char *assignChar(const char *source, char **dest)
{
    // Allocate space.

    char *new_str = malloc((strlen(source) + 1) * sizeof(char));
    if (new_str == NULL)
        return NULL;
    strcpy(new_str, source);
    *dest = new_str;
    return new_str;
}

// // TODO TEST: mapCreate: Creates new map object - Needs to be tested
Map mapCreate()
{
    // Allocate pair.
    Map new_map = malloc(sizeof(Map));
    if (new_map == NULL)
        return NULL;
    new_map->data = malloc(sizeof(Node));
    if (new_map->data == NULL)
        return NULL;
    ((new_map)->data)->data = malloc(sizeof(MapPair));
    if (((new_map)->data)->data == NULL)
        return NULL;
    // Allocate integer space for iterator
    // Change iterator status
    // new_map->iterator = (int)*(malloc(sizeof(int)));
    // (new_map)->iterator = 0;
    // TODO: Tackle leak issue with iterator
    // Allocate new map.
    return new_map;
}

void mapDestroy(Map map)
{
    if (map == NULL)
        return;
    // Go through the linked list
    freeNodes(map->data);
    free(map);
}

Map mapCopy(Map map)
{
    if (map == NULL)
        return NULL;
    // Allocate a new map.
    Map new_map = malloc(sizeof(Map));
    if (new_map == NULL)
        return NULL;
    // Allocate a new starting data node
    Node start_node = malloc(sizeof(Node));
    if (start_node == NULL)
    {
        mapDestroy(new_map);
        return NULL;
    }
    new_map->data = start_node;
    // Start node is correctly allocated. Allocate starting pair.
    MapPair start_pair = malloc(sizeof(MapPair));
    if (start_pair == NULL)
    {
        mapDestroy(new_map);
        return NULL;
    }
    start_node->data = start_pair;
    // Check the first node and allocate the correct values
    Node current_copy = start_node, previous_copy = start_node;
    if (map->data != NULL)
    {
        // Allocate the data into the node.
        if (assignChar(map->data->data->key, &(start_pair->key)) == NULL ||
            assignChar(map->data->data->value, &(start_pair->value)) == NULL)
        {
            mapDestroy(new_map);
            return NULL;
        }
    }
    // Assign the current and previous node, iterate through.
    Node current_node = map->data;
    while (current_node->next != NULL)
    {
        // Allocate a new node for current copy
        current_copy = malloc(sizeof(Node));
        if (current_copy == NULL)
        {
            mapDestroy(new_map);
            return NULL;
        }
        // Create a new pair for the node.
        MapPair current_pair = malloc(sizeof(MapPair));
        if (current_pair == NULL)
        {
            freeNode(current_copy);
            mapDestroy(new_map);
            return NULL;
        }
        current_copy->data = current_pair;
        // Assign the values.
        if (assignChar(current_node->data->key, &(current_pair->key)) == NULL ||
            assignChar(current_node->data->value, &(current_pair->value)) == NULL)
        {
            freeNode(current_copy);
            mapDestroy(new_map);
            return NULL;
        }
        // We assigned everything successfully. Assign current node as previous' next and cycle.
        previous_copy->next = current_copy;
        previous_copy = previous_copy->next;
        current_node = current_node->next;
    }
    return map;
}

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

Node createNewNode(const char *key, const char *data)
{
    if (key == NULL || data == NULL)
        return NULL;
    Node new_node = malloc(sizeof(Node));
    if (new_node == NULL)
        return NULL;
    // Create a new map pair.
    new_node->data = malloc(sizeof(MapPair));
    if (new_node->data == NULL)
    {
        freeNode(new_node);
        return NULL;
    }
    char *key_str = (char *)malloc(sizeof(char) * (1 + strlen(key)));
    char *val_str = malloc(sizeof(char) * (1 + strlen(data)));
    // Assign the values.
    // Allocate strings for key and value.
    // new_node->data->key =
    if (assignChar(key, &key_str) == NULL ||
        assignChar(data, &val_str) == NULL)
    {
        freeNode(new_node);
        return NULL;
    }
    new_node->data->key = key_str;
    new_node->data->value = val_str;
    return new_node;
}

// TODO: Complete mapPut.
MapResult mapPut(Map map, const char *key, const char *data)
{
    if (map == NULL || key == NULL || data == NULL)
        return MAP_NULL_ARGUMENT;
    // Iterate over the given map.
    Node current_node = map->data;
    // Check if the first node is null.
    if (current_node == NULL || current_node->data == NULL || current_node->data->key == NULL)
    {
        // Assign new node.
        Node new_node = createNewNode(key, data);
        if (new_node == NULL)
            return MAP_NULL_ARGUMENT;
        // Assign the new node to the map itself.
        map->data = new_node;
        return MAP_SUCCESS;
    }
    while (current_node != NULL)
    {
        // Check the current node.
        if (strcmp(current_node->data->key, key) == 0)
        {
            // We located the required key. Assign char into the value and return success.
            if (assignChar(data, &(current_node->data->value)) == NULL)
                return MAP_OUT_OF_MEMORY;
            return MAP_SUCCESS;
        }

        if (current_node->next == NULL)
        {
            // We reached the last node. Create a new node, assign the values and return.
            Node new_node = createNewNode(key, data);
            if (new_node == NULL)
                return MAP_NULL_ARGUMENT;
            // Assign the new node to the map itself.
            current_node->next = new_node;
            return MAP_SUCCESS;
        }
    }
    return MAP_ERROR;
}

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
        current_pair = current_pair->next;
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
        freeNode(current_pair);
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
            freeNode(next_pair);
            return MAP_SUCCESS;
        }
        // Go on to the next node.
        current_pair = current_pair->next;
    }
    // Reached the end, no comparison positives. Return no items in list.
    return MAP_ITEM_DOES_NOT_EXIST;
}

// TODO: mapGetFirst: Retrieves first key in map
char *mapGetFirst(Map map);

// TODO: mapGetNext: Retrieves next key in line
char *mapGetNext(Map map);

// TODO: mapClear: Clears the map from key-value pairs
MapResult mapClear(Map map);

int main()
{
    Map map = mapCreate();
    if (map == NULL)
    {
        return 0;
    }
    mapPut(map, "308324772", "John Snow");
    mapPut(map, "208364702", "Sansa Stark");
    mapPut(map, "308324772", "The Night King");
    char *name = mapGet(map, "308324772");    // name = "The Night King"
    name = mapGet(map, "208364702");          // name = "Sansa Stark"
    bool res = mapContains(map, "108364702"); // res = false
    if (res)
        return 1;
    printf("%s", name);
}
#include "map.h"

// mapCreate: Creates new map object
Map mapCreate()
{
    // Allocate new map.
    return malloc(sizeof(Map));
}

// TODO: MapDestroy, removes all elements and frees allocation.
void mapDestroy(Map map) {}

// TODO: mapCopy: Copies map into new one
Map mapCopy(Map map) {}

// TODO: mapGetSize: Returns number of keys in map
int mapGetSize(Map map) {}

// TODO: mapContains: True/false if key exists in map
bool mapContains(Map map, const char *key) {}

// TODO: mapPut: Changes value of key or adds key-value pair
MapResult mapPut(Map map, const char *key, const char *data) {}

// TODO: mapGet: Retrieves value of key
char *mapGet(Map map, const char *key) {}

// TODO: mapRemove: Removes key-value pair
MapResult mapRemove(Map map, const char *key) {}

// TODO: mapGetFirst: Retrieves first key in map
char *mapGetFirst(Map map) {}

// TODO: mapGetNext: Retrieves next key in line
char *mapGetNext(Map map) {}

// TODO: mapClear: Clears the map from key-value pairs
MapResult mapClear(Map map) {}
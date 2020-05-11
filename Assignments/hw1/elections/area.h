#ifndef AREA_H
#define AREA_H

#include <stdlib.h>
#include <string.h>
#include "call_result.h"

typedef struct area_t
{
    int id;
    char *name;
} * Area;

char *areaGetName(Area area);
int areaGetId(Area area);

CallResult areaSetName(Area area, const char *name);
CallResult areaSetId(Area area, int id);

char *areaGetName(Area area)
{
    if (area == NULL)
    {
        return NULL;
    }
    return area->name;
}

int areaGetId(Area area)
{
    if (area == NULL)
    {
        return -1;
    }
    return area->id;
}

CallResult areaSetName(Area area, const char *name)
{
    if (area == NULL || name == NULL)
    {
        return ASSIGN_NULL;
    }
    // Allocate new char
    char *new_name = malloc(sizeof(char) * (1 + strlen(name)));
    if (new_name == NULL)
    {
        return ASSIGN_MEMORY;
    }
    // Copy the string.
    strcpy(new_name, name);
    // Assign.
    free(area->name);
    area->name = new_name;
    return ASSIGN_SUCCESS;
}

CallResult areaSetId(Area area, int id)
{
    area->id = id;
    return ASSIGN_SUCCESS;
}
#endif // AREA_H
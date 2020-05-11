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

char *getAreaName(Area area);
int getAreaId(Area area);
Area createArea(int id, const char *name);
void destroyArea(Area area);

CallResult setAreaName(Area area, const char *name);
CallResult setAreaId(Area area, int id);

char *getAreaName(Area area)
{
    if (area == NULL)
    {
        return NULL;
    }
    return area->name;
}

int getAreaId(Area area)
{
    if (area == NULL)
    {
        return -1;
    }
    return area->id;
}

CallResult setAreaName(Area area, const char *name)
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

CallResult setAreaId(Area area, int id)
{
    area->id = id;
    return ASSIGN_SUCCESS;
}

Area createArea(int id, const char *name)
{
    if (id <= 0 || name == NULL)
    {
        return NULL;
    }
    Area area = malloc(sizeof(*area));
    if (area == NULL)
    {
        return NULL;
    }
    area->name = NULL;
    area->id = 0;
    setAreaId(area, id);
    if (setAreaName(area, name) != ASSIGN_SUCCESS)
    {
        // Destroy and return null.
        destroyArea(area);
        return NULL;
    }
    return area;
}

void destroyArea(Area area)
{
    if (area == NULL)
    {
        return;
    }
    // Free the name, id and the area.
    free(area->name);
    area->name = NULL;
    free(area);
    area = NULL;
}

#endif // AREA_H
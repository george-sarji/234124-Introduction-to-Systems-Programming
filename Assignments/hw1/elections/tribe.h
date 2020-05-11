#ifndef TRIBE_H
#define TRIBE_H

#include "assign.h"

typedef struct tribe_t
{
    int id;
    char *name;
} * Tribe;

char *tribeGetName(Tribe tribe);
int tribeGetId(Tribe tribe);

AssignResult tribeSetName(Tribe tribe, const char *name);
AssignResult tribeSetId(Tribe tribe, int id);

char *tribeGetName(Tribe tribe)
{
    if (tribe == NULL)
    {
        return NULL;
    }
    return tribe->name;
}

int tribeGetId(Tribe tribe)
{
    if (tribe == NULL)
    {
        return NULL;
    }
    return tribe->id;
}

AssignResult tribeSetName(Tribe tribe, const char *name)
{
    if (tribe == NULL || name == NULL)
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
    free(tribe->name);
    tribe->name = new_name;
    return ASSIGN_SUCCESS;
}

AssignResult tribeSetId(Tribe tribe, int id)
{
    tribe->id = id;
    return ASSIGN_SUCCESS;
}

#endif // TRIBE_H
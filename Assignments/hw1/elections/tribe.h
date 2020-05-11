#ifndef TRIBE_H
#define TRIBE_H

#include "call_result.h"

typedef struct tribe_t
{
    int id;
    char *name;
} * Tribe;

char *getTribeName(Tribe tribe);
int getTribeId(Tribe tribe);
Tribe createTribe(int id, const char *name);
void destroyTribe(Tribe tribe);

CallResult setTribeName(Tribe tribe, const char *name);
CallResult setTribeId(Tribe tribe, int id);

char *getTribeName(Tribe tribe)
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
        return -1;
    }
    return tribe->id;
}

Tribe createTribe(int id, const char *name)
{
    if (id <= 0 || name == NULL)
    {
        return NULL;
    }
    Tribe tribe = malloc(sizeof(*tribe));
    if (tribe == NULL)
    {
        return NULL;
    }
    // Set the ID and name.
    setTribeId(tribe, id);
    tribe->name = NULL;
    if (setTribeName(tribe, name) == ASSIGN_MEMORY)
    {
        destroyTribe(tribe);
        return NULL;
    }
    return tribe;
}

void destroyTribe(Tribe tribe)
{
    if (tribe == NULL)
    {
        return;
    }
    // Free the name, id and the tribe.
    free(tribe->name);
    tribe->name = NULL;
    free(tribe);
    tribe = NULL;
}

CallResult setTribeName(Tribe tribe, const char *name)
{
    if (tribe == NULL)
    {
        return ASSIGN_NULL;
    }
    else if (name == NULL)
    {
        tribe->name = NULL;
        return ASSIGN_NULL;
    }
    // Allocate new char
    char *new_name = malloc(sizeof(char) * (1 + strlen(name)));
    if (new_name == NULL)
    {
        return ASSIGN_MEMORY;
    }
    else
    {
        // Copy the string.
        strcpy(new_name, name);
        // Assign.
        free(tribe->name);
        tribe->name = new_name;
        return ASSIGN_SUCCESS;
    }
    return ASSIGN_UNK_ERROR;
}

CallResult setTribeId(Tribe tribe, int id)
{
    tribe->id = id;
    return ASSIGN_SUCCESS;
}

#endif // TRIBE_H
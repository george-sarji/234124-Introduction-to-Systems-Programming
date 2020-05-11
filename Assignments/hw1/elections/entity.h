#ifndef ENTITY_H
#define ENTITY_H

#include "call_result.h"
#include <stdlib.h>
#include <string.h>

typedef struct entity_t
{
    int id;
    char *name;
} * Entity;

char *getEntityName(Entity entity);
int getEntityId(Entity entity);
Entity createEntity(int id, const char *name);
void destroyEntity(Entity entity);

CallResult setEntityName(Entity entity, const char *name);
CallResult setEntityId(Entity entity, int id);

char *getEntityName(Entity entity)
{
    if (entity == NULL)
    {
        return NULL;
    }
    return entity->name;
}

int entityGetId(Entity entity)
{
    if (entity == NULL)
    {
        return -1;
    }
    return entity->id;
}

Entity createEntity(int id, const char *name)
{
    if (id <= 0 || name == NULL)
    {
        return NULL;
    }
    Entity entity = malloc(sizeof(*entity));
    if (entity == NULL)
    {
        return NULL;
    }
    // Set the ID and name.
    setEntityId(entity, id);
    entity->name = NULL;
    if (setEntityName(entity, name) == ASSIGN_MEMORY)
    {
        destroyEntity(entity);
        return NULL;
    }
    return entity;
}

void destroyEntity(Entity entity)
{
    if (entity == NULL)
    {
        return;
    }
    // Free the name, id and the entity.
    free(entity->name);
    entity->name = NULL;
    free(entity);
    entity = NULL;
}

CallResult setEntityName(Entity entity, const char *name)
{
    if (entity == NULL)
    {
        return ASSIGN_NULL;
    }
    else if (name == NULL)
    {
        entity->name = NULL;
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
        free(entity->name);
        entity->name = new_name;
        return ASSIGN_SUCCESS;
    }
    return ASSIGN_UNK_ERROR;
}

CallResult setEntityId(Entity entity, int id)
{
    entity->id = id;
    return ASSIGN_SUCCESS;
}

#endif // TRIBE_H
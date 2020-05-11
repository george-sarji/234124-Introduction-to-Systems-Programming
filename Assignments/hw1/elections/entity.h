#ifndef ENTITY_H
#define ENTITY_H

#include "call_result.h"
#include "election.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum entityType_t
{
    ENTITY_TRIBE,
    ENTITY_AREA,
    ENTITY_NULL
} EntityType;
typedef struct entity_t
{
    int id;
    char *name;
    enum entityType_t type;
    struct entity_t *next;
} * Entity;

char *getEntityName(Entity entity);
char *getEntityNameCopy(Entity entity);
int getEntityId(Entity entity);
Entity createTribe(int id, const char *name);
Entity createArea(int id, const char *name);
Entity createEntity(int id, const char *name, EntityType type);
void destroyEntity(Entity entity);
EntityType getEntityType(Entity entity);
bool isEntityIdentical(Entity ent1, Entity ent2);
bool isSameEntityId(Entity ent1, int id);
Entity getNextEntity(Entity entity);
CallResult setNextEntity(Entity entity, Entity next);
ElectionResult addEntity(Entity entity, int id, const char *name, EntityType type);

CallResult setEntityName(Entity entity, const char *name);
CallResult setEntityId(Entity entity, int id);

Entity getNextEntity(Entity entity)
{
    if (entity == NULL)
    {
        return NULL;
    }
    return entity->next;
}

CallResult setNextEntity(Entity entity, Entity next)
{
    if (entity == NULL)
    {
        return ASSIGN_NULL;
    }
    entity->next = next;
    return ASSIGN_SUCCESS;
}

bool isSameEntityId(Entity ent1, int id)
{
    return ent1 != NULL && getEntityId(ent1) == id;
}

bool isEntityIdentical(Entity ent1, Entity ent2)
{
    return ent1 != NULL && ent2 != NULL && getEntityType(ent1) == getEntityType(ent2) && getEntityId(ent1) == getEntityId(ent2);
}

Entity createTribe(int id, const char *name)
{
    return createEntity(id, name, ENTITY_TRIBE);
}

Entity createArea(int id, const char *name)
{
    return createEntity(id, name, ENTITY_AREA);
}

EntityType getEntityType(Entity entity)
{
    if (entity == NULL)
    {
        return ENTITY_NULL;
    }
    return entity->type;
}

char *getEntityName(Entity entity)
{
    if (entity == NULL)
    {
        return NULL;
    }
    return entity->name;
}

int getEntityId(Entity entity)
{
    if (entity == NULL)
    {
        return -1;
    }
    return entity->id;
}

Entity createEntity(int id, const char *name, EntityType type)
{
    if (!isLegalId(id) || name == NULL)
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
    entity->type = type;
    entity->next = NULL;
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

ElectionResult addEntity(Entity entity, int id, const char *name, EntityType type)
{
    if (entity == NULL || name == NULL)
    {
        return ELECTION_NULL_ARGUMENT;
    }
    if (!isLegalId(id))
    {
        return ELECTION_INVALID_ID;
    }
    if (!isLegalName(name))
    {
        return ELECTION_INVALID_NAME;
    }
    // Go through the entities.
    Entity current = entity;
    while (current != NULL)
    {
        // Check if they're identical.
        if (isSameEntityId(current, id))
        {
            // Active entity. Return.
            return type == ENTITY_TRIBE ? ELECTION_TRIBE_ALREADY_EXIST : ELECTION_AREA_ALREADY_EXIST;
        }
        if (getNextEntity(current) == NULL)
        {
            // Create the new entity.
            Entity new_entity = createEntity(id, name, type);
            if (new_entity == NULL)
            {
                return ELECTION_OUT_OF_MEMORY;
            }
            setNextEntity(current, new_entity);
            return ELECTION_SUCCESS;
        }
    }
    return ELECTION_SUCCESS;
}

char *getEntityNameCopy(Entity entity)
{
    if (entity == NULL || getEntityName(entity) == NULL)
    {
        return NULL;
    }
    // Allocate new string.
    char *new_str = malloc(sizeof(char) * (1 + strlen(getEntityName(entity))));
    if (new_str == NULL)
    {
        return NULL;
    }
    strcpy(new_str, getEntityName(entity));
    return new_str;
}

#endif // TRIBE_H
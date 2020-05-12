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

// * Declarations
// ! Create/Destroy
Entity createTribe(int id, const char *name);
Entity createArea(int id, const char *name);
Entity createEntity(int id, const char *name, EntityType type);
void destroyEntity(Entity entity);

// ! Get
char *getEntityName(Entity entity);
char *getEntityNameCopy(Entity entity);
int getEntityId(Entity entity);
EntityType getEntityType(Entity entity);
Entity getNextEntity(Entity entity);

// ! Set
CallResult setEntityName(Entity entity, const char *name);
CallResult setEntityId(Entity entity, int id);
CallResult setNextEntity(Entity entity, Entity next);

// ! Misc
bool isEntityIdentical(Entity ent1, Entity ent2);
bool isSameEntityId(Entity ent1, int id);
ElectionResult addEntity(Entity entity, int id, const char *name, EntityType type, Entity *entity_ptr);

#endif // TRIBE_H
#include "entity.h"
#include "call_result.h"
#include "election.h"
#include "ballot.h"
#include "ballotbox.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>

struct election_t
{
    struct entity_t *areas;
    struct entity_t *tribes;
    struct areaBallot_t *area_ballots;
};

Entity getElectionTribes(Election election);
Entity getElectionAreas(Election election);
Entity getElectionEntities(Election election, EntityType type);
void setElectionEntities(Election election, Entity entity, EntityType type);
AreaBallot getElectionAreaBallots(Election election);
void destroyElectionEntities(Entity entity);
ElectionResult addElectionAreaBallot(Election election, Entity new_area);
ElectionResult addElectionBallotBox(Election election, Entity new_tribe);
ElectionResult electionAddEntity(Election election, int id, const char *name, EntityType type);
ElectionResult setElectionEntityName(Election election, int id, const char *name, EntityType type);
Election electionCreate();
void electionDestroy(Election election);
Entity getElectionTribes(Election election)
{
    if (election == NULL)
    {
        return NULL;
    }
    return election->tribes;
}

Entity getElectionEntities(Election election, EntityType type)
{
    if (election == NULL)
    {
        return NULL;
    }
    return type == ENTITY_TRIBE ? election->tribes : election->areas;
}

void setElectionEntities(Election election, Entity entity, EntityType type)
{
    if (election == NULL || entity == NULL)
    {
        return;
    }
    if (type == ENTITY_TRIBE)
    {
        election->tribes = entity;
    }
    else
    {
        election->areas = entity;
    }
}

Entity getElectionAreas(Election election)
{
    if (election == NULL)
    {
        return NULL;
    }
    return election->areas;
}

AreaBallot getElectionAreaBallots(Election election)
{
    if (election == NULL)
    {
        return NULL;
    }
    return election->area_ballots;
}

// ElectionResult addElectionAreaBallot(Election election, Entity new_area)
// {
//     if (election == NULL)
//     {
//         return ELECTION_NULL_ARGUMENT;
//     }
//     // We need to add a new area ballot. Create a new one.
//     AreaBallot new_ballot = createAreaBallot(new_area);
//     if (new_ballot == NULL)
//     {
//         return ELECTION_OUT_OF_MEMORY;
//     }

// }

Election electionCreate()
{
    // Allocate new election.
    Election election = malloc(sizeof(*election));
    if (election == NULL)
    {
        return NULL;
    }
    // Nullify areas, tribes and ballots.
    election->areas = NULL;
    election->tribes = NULL;
    election->area_ballots = NULL;
    return election;
}

void destroyElectionEntities(Entity entity)
{
    while (entity != NULL)
    {
        Entity next_entity = getNextEntity(entity);
        destroyEntity(entity);
        entity = NULL;
        entity = next_entity;
    }
}

void electionDestroy(Election election)
{
    if (election == NULL)
    {
        return;
    }
    // Destroy the entities.
    destroyElectionEntities(getElectionTribes(election));
    destroyElectionEntities(getElectionAreas(election));
    destroyAreaBallots(getElectionAreaBallots(election));
    election->area_ballots = NULL;
    election->areas = NULL;
    election->tribes = NULL;
    free(election);
    election = NULL;
}

ElectionResult electionAddEntity(Election election, int id, const char *name, EntityType type)
{
    if (election == NULL || name == NULL)
    {
        return ELECTION_NULL_ARGUMENT;
    }
    Entity entities = getElectionEntities(election, type);
    if (entities == NULL)
    {
        Entity new_entry = createEntity(id, name, type);
        if (new_entry == NULL)
        {
            electionDestroy(election);
            return ELECTION_OUT_OF_MEMORY;
        }
        setElectionEntities(election, new_entry, type);
        // Add a new area ballot or a new ballot box in each area.
        if (type == ENTITY_TRIBE)
        {
            // TODO: Add ballot box in each area ballot
        }
        else
        {
            // TODO: Add new area ballot
        }
        return ELECTION_SUCCESS;
    }
    else
    {
        ElectionResult result = addEntity(entities, id, name, type);
        if (result == ELECTION_OUT_OF_MEMORY)
        {
            electionDestroy(election);
        }
        return result;
    }
}

// TODO: Add the ballot boxes
ElectionResult electionAddTribe(Election election, int tribe_id, const char *tribe_name)
{
    return electionAddEntity(election, tribe_id, tribe_name, ENTITY_TRIBE);
}
// TODO: Add the area ballots
ElectionResult electionAddArea(Election election, int area_id, const char *area_name)
{
    return electionAddEntity(election, area_id, area_name, ENTITY_AREA);
}

char *getSpecificEntityName(Election election, int id, EntityType type)
{
    Entity entities = getElectionEntities(election, type);
    // Go through the entities.
    while (entities != NULL)
    {
        if (isSameEntityId(entities, id))
        {
            // We found the entity. Return the name.
            return getEntityNameCopy(entities);
        }
        entities = getNextEntity(entities);
    }
    return NULL;
}

char *electionGetTribeName(Election election, int tribe_id)
{
    return getSpecificEntityName(election, tribe_id, ENTITY_TRIBE);
}

// TODO: Complete function for electionSetTribeName
// ElectionResult setElectionEntityName(Election election, int id, const char *name, EntityType type)
// {
//     if (election == NULL || name == NULL)
//     {
//         return ELECTION_NULL_ARGUMENT;
//     }
//     if (isLegalId(id))
//     {
//         return ELECTION_INVALID_ID;
//     }
//     if (isLegalName(name))
//     {
//         return ELECTION_INVALID_NAME;
//     }

// }

// int main()
// {
//     Election el = electionCreate();
//     Entity tribe = createTribe(1, "test");
//     printf("%s", getEntityName(tribe));
//     setEntityId(tribe, 5);
//     setEntityName(tribe, "lmao this works");
//     BallotBox ballot = createBallot(tribe);
//     removeBallotVotes(ballot, 50);
//     electionAddTribe(el, 10, "Test tribe");
//     char *name = electionGetTribeName(el, 10);
//     assert(strcmp(name, "Test tribe") == 0);
//     printf("%s", name);
//     free(name);
//     electionAddArea(el, 10, "Test tribe");
//     destroyBallot(ballot);
//     destroyEntity(tribe);
//     tribe = NULL;

//     Entity area = createArea(2, "area");
//     printf("%s", getEntityName(area));
//     setEntityId(area, 5);
//     setEntityName(area, "woah");
//     destroyEntity(area);
//     area = NULL;

//     electionDestroy(el);

//     assert(isLegalName("test") == true);
//     // printf("%d", isLegalName("test"));
//     // tribe = NULL;
//     return 0;
// }
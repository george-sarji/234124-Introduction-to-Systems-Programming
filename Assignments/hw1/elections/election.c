#include "entity.h"
#include "call_result.h"
#include "election.h"
#include "ballot.h"
#include "ballotbox.h"
#include "util.h"
#include <string.h>
#include <assert.h>
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

// * Declarations
// ! Create/Destroy
void destroyElectionEntities(Entity entity);

// ! Set
void setElectionEntities(Election election, Entity entity, EntityType type);
void setElectionBallots(Election election, AreaBallot ballot);

// ! Get
Entity getElectionTribes(Election election);
Entity getElectionAreas(Election election);
Entity getElectionEntities(Election election, EntityType type);
AreaBallot getElectionAreaBallots(Election election);
char *getSpecificEntityName(Election election, int id, EntityType type);

// ! Misc
void removeAreaBallots(Election election, AreaBallot ballot, int area_id);
ElectionResult addElectionAreaBallot(Election election, Entity new_area);
ElectionResult addElectionBallotBox(Election election, Entity new_tribe);
ElectionResult electionAddEntity(Election election, int id, const char *name, EntityType type);

// * Logic

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

void setElectionEntities(Election election, Entity entity, EntityType type)
{
    if (election == NULL || entity == NULL)
    {
        return;
    }
    if (type == ENTITY_TRIBE)
    {
        free(election->tribes);
        election->tribes = NULL;
        election->tribes = entity;
    }
    else
    {
        free(election->areas);
        election->areas = NULL;
        election->areas = entity;
    }
}

void setElectionBallots(Election election, AreaBallot ballot)
{
    if (election == NULL)
    {
        return;
    }
    election->area_ballots = ballot;
}

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

void removeAreaBallots(Election election, AreaBallot ballot, int area_id)
{
    if (election == NULL || ballot == NULL || !isLegalId(area_id))
    {
        return;
    }
    // Check if the first box is the actual culprit.
    if (ballot != NULL && isSameEntityId(getBallotArea(ballot), area_id))
    {
        // First ballot needs to be removed.
        setElectionBallots(election, getNextAreaBallot(ballot));
        destroyAreaBallot(ballot);
    }
    else
    {
        AreaBallot current = getNextAreaBallot(ballot), previous = ballot;
        while (current != NULL)
        {
            if (isSameEntityId(getBallotArea(current), area_id))
            {
                // Remove this ballot.
                setNextAreaBallot(previous, getNextAreaBallot(current));
                destroyAreaBallot(current);
                return;
            }
            previous = current;
            current = getNextAreaBallot(current);
        }
    }
}

ElectionResult electionAddEntity(Election election, int id, const char *name, EntityType type)
{
    if (election == NULL || name == NULL)
    {
        return ELECTION_NULL_ARGUMENT;
    }
    else if (!isLegalName(name))
    {
        return ELECTION_INVALID_NAME;
    }
    else if (!isLegalId(id))
    {
        return ELECTION_INVALID_ID;
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
    }
    else
    {
        ElectionResult result = addEntity(entities, id, name, type);
        if (result == ELECTION_OUT_OF_MEMORY)
        {
            electionDestroy(election);
            return result;
        }
        else if (result != ELECTION_SUCCESS)
        {
            return result;
        }
    }
    // Add a new area ballot or a new ballot box in each area.
    while (entities != NULL)
    {
        if (isSameEntityId(entities, id))
        {
            // We found the entity.
            if (type == ENTITY_TRIBE)
            {
                // TODO: Add with the tribe.
                AreaBallot ballots = getElectionAreaBallots(election);
                if (addTribeBoxes(ballots, entities) == ASSIGN_MEMORY)
                {
                    electionDestroy(election);
                    return ELECTION_OUT_OF_MEMORY;
                }
            }
            else
            {
                // TODO: Add new area ballot.
                AreaBallot ballot = createAreaBallot(entities, getElectionTribes(election));
                if (ballot == NULL)
                {
                    destroyAreaBallots(ballot);
                    electionDestroy(election);
                    return ELECTION_OUT_OF_MEMORY;
                }
                // Get the current ballots.
                AreaBallot current = getElectionAreaBallots(election);
                if (current == NULL)
                {
                    setElectionBallots(election, ballot);
                }
                else
                {
                    insertAreaBallot(current, ballot);
                }
            }
        }
        entities = getNextEntity(entities);
    }
    return ELECTION_SUCCESS;
}

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

char *electionGetTribeName(Election election, int tribe_id)
{
    return getSpecificEntityName(election, tribe_id, ENTITY_TRIBE);
}

// TODO: Complete function for electionSetTribeName
ElectionResult electionSetTribeName(Election election, int tribe_id, const char *tribe_name)
{
    // Check if any are null.
    if (election == NULL || tribe_name == NULL)
    {
        return ELECTION_NULL_ARGUMENT;
    }
    if (!isLegalName(tribe_name))
    {
        return ELECTION_INVALID_NAME;
    }
    if (!isLegalId(tribe_id))
    {
        return ELECTION_INVALID_ID;
    }
    // Go through the entities.
    Entity current = getElectionTribes(election);
    while (current != NULL)
    {
        // Compare the ID.
        if (isSameEntityId(current, tribe_id))
        {
            // We found the tribe. Set the name and return.
            if (setEntityName(current, tribe_name) != ASSIGN_SUCCESS)
            {
                return ELECTION_OUT_OF_MEMORY;
            }
            return ELECTION_SUCCESS;
        }
        // Go through to the next.
        current = getNextEntity(current);
    }
    return ELECTION_TRIBE_NOT_EXIST;
}

ElectionResult electionRemoveTribe(Election election, int tribe_id)
{
    if (election == NULL)
    {
        return ELECTION_NULL_ARGUMENT;
    }
    else if (!isLegalId(tribe_id))
    {
        return ELECTION_INVALID_ID;
    }
    // Go over the tribes and remove the given tribe.
    Entity tribe = getElectionTribes(election);
    while (tribe != NULL)
    {
        if (isSameEntityId(tribe, tribe_id))
        {
            // We found the tribe. Destroy it and destroy the related ballots.
            AreaBallot ballot = getElectionAreaBallots(election);
            removeTribeBallots(ballot, tribe_id);
            destroyEntity(tribe);
            return ELECTION_SUCCESS;
        }
        tribe = getNextEntity(tribe);
    }
    return ELECTION_TRIBE_NOT_EXIST;
}

int main()
{
    Election election = electionCreate();
    electionAddTribe(election, 1, "tribe");
    electionAddTribe(election, 2, "tribe");
    electionAddArea(election, 1, "area");
    assert(electionAddArea(election, 2, "second area") == ELECTION_SUCCESS);
    // assert(electionRemoveTribe(election, 2) == ELECTION_SUCCESS);
    electionSetTribeName(election, 1, "tribe name changed");
    char *name = electionGetTribeName(election, 1);
    assert(strcmp(name, "tribe name changed") == 0);
    electionDestroy(election);
    free(name);
    election = NULL;
    return 0;
}
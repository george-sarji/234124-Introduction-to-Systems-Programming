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
ElectionResult modifyVotes(AreaBallot ballot, int area_id, int tribe_id, int num_of_votes);

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
        election->tribes = entity;
    }
    else
    {
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
    // If the first area ballot is not the one we're looking for, carry on.
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
    Entity new_entity = NULL;
    if (entities == NULL)
    {
        Entity new_entry = createEntity(id, name, type);
        new_entity = new_entry;
        if (new_entry == NULL)
        {
            electionDestroy(election);
            return ELECTION_OUT_OF_MEMORY;
        }
        setElectionEntities(election, new_entry, type);
        // Add logic here.
    }
    else
    {
        ElectionResult result = addEntity(entities, id, name, type, &new_entity);
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
    // We found the entity.
    if (type == ENTITY_TRIBE)
    {
        // TODO: Add with the tribe.
        AreaBallot ballots = getElectionAreaBallots(election);
        if (addTribeBoxes(ballots, new_entity) == ASSIGN_MEMORY)
        {
            electionDestroy(election);
            return ELECTION_OUT_OF_MEMORY;
        }
    }
    else
    {
        // TODO: Add new area ballot.
        AreaBallot ballot = createAreaBallot(new_entity, getElectionTribes(election));
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
    return ELECTION_SUCCESS;
}

ElectionResult modifyVotes(AreaBallot ballot, int area_id, int tribe_id, int num_of_votes)
{
    while (ballot != NULL)
    {
        if (isSameEntityId(getBallotArea(ballot), area_id))
        {
            // Add votes to this ballot.
            BallotBox box = getTribeBallotBox(getAreaBallotBoxes(ballot), tribe_id);
            if (box == NULL)
            {
                return ELECTION_TRIBE_NOT_EXIST;
            }
            // Add the votes and return.
            if (num_of_votes < 0)
            {
                return removeBallotVotes(box, -num_of_votes);
            }
            else
            {
                return addBallotVotes(box, num_of_votes);
            }
        }
        ballot = getNextAreaBallot(ballot);
    }
    return ELECTION_AREA_NOT_EXIST;
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
    AreaBallot ballot = getElectionAreaBallots(election);
    removeTribeBallots(ballot, tribe_id);
    // Find the tribe. Check if first?
    if (tribe != NULL && isSameEntityId(tribe, tribe_id))
    {
        // Remove first tribe.
        setElectionEntities(election, getNextEntity(tribe), ENTITY_TRIBE);
        destroyEntity(tribe);
        return ELECTION_SUCCESS;
    }
    Entity previous = tribe;
    tribe = getNextEntity(tribe);
    while (tribe != NULL)
    {
        if (tribe != NULL && isSameEntityId(tribe, tribe_id))
        {
            // Remove the tribe from the chain.
            setNextEntity(previous, getNextEntity(tribe));
            destroyEntity(tribe);
            return ELECTION_SUCCESS;
        }
        previous = tribe;
        tribe = getNextEntity(tribe);
    }
    return ELECTION_TRIBE_NOT_EXIST;
}

ElectionResult electionRemoveAreas(Election election, AreaConditionFunction should_delete_area)
{
    if (election == NULL || should_delete_area == NULL)
    {
        return ELECTION_NULL_ARGUMENT;
    }
    Entity area = getElectionAreas(election);
    // Check if the first area is what we want.
    while (area != NULL && should_delete_area(getEntityId(area)))
    {
        // Delete this area.
        Entity next = getNextEntity(area);
        removeAreaBallots(election, getElectionAreaBallots(election), getEntityId(area));
        destroyEntity(area);
        setElectionEntities(election, next, ENTITY_AREA);
        area = next;
    }
    Entity previous = area;
    if (area == NULL && getNextEntity(area) == NULL)
    {
        return ELECTION_SUCCESS;
    }
    area = getNextEntity(area);
    while (previous != NULL && area != NULL)
    {
        if (should_delete_area(getEntityId(area)))
        {
            removeAreaBallots(election, getElectionAreaBallots(election), getEntityId(area));
            setNextEntity(previous, getNextEntity(area));
            destroyEntity(area);
            area = getNextEntity(previous);
            continue;
        }
        previous = area;
        area = getNextEntity(area);
    }
    return ELECTION_SUCCESS;
}

ElectionResult electionAddVote(Election election, int area_id, int tribe_id, int num_of_votes)
{
    if (election == NULL)
    {
        return ELECTION_NULL_ARGUMENT;
    }
    else if (!isLegalId(area_id) || !isLegalId(tribe_id))
    {
        return ELECTION_INVALID_ID;
    }
    else if (num_of_votes <= 0)
    {
        return ELECTION_INVALID_VOTES;
    }
    else
    {
        // We need to get the area.
        return modifyVotes(getElectionAreaBallots(election), area_id, tribe_id, num_of_votes);
    }
}

ElectionResult electionRemoveVote(Election election, int area_id, int tribe_id, int num_of_votes)
{
    if (election == NULL)
    {
        return ELECTION_NULL_ARGUMENT;
    }
    else if (!isLegalId(area_id) || !isLegalId(tribe_id))
    {
        return ELECTION_INVALID_ID;
    }
    else if (num_of_votes <= 0)
    {
        return ELECTION_INVALID_VOTES;
    }
    else
    {
        // We need to get the area.
        return modifyVotes(getElectionAreaBallots(election), area_id, tribe_id, -num_of_votes);
    }
}

// int main()
// {
//     Election election = electionCreate();
//     electionAddTribe(election, 1, "tribe");
//     electionAddTribe(election, 2, "tribe");
//     electionAddArea(election, 1, "area");
//     assert(electionAddArea(election, 2, "second area") == ELECTION_SUCCESS);
//     assert(electionRemoveTribe(election, 2) == ELECTION_SUCCESS);
//     electionSetTribeName(election, 1, "tribe name changed");
//     char *name = electionGetTribeName(election, 1);
//     assert(strcmp(name, "tribe name changed") == 0);
//     electionDestroy(election);
//     free(name);
//     election = NULL;
//     return 0;
// }
#include "entity.h"
#include "call_result.h"
#include "election.h"
#include "ballot.h"
#include "ballotbox.h"
#include <stdio.h>
#include <stdlib.h>

struct election_t
{
    struct entity_t *areas;
    struct entity_t *tribes;
    struct areaBallot_t *area_ballots;
};

Entity getElectionTribes(Election election);
Entity getElectionAreas(Election election);
AreaBallot getElectionAreaBallots(Election election);

Entity getElectionTribes(Election election)
{
    if (election == NULL)
    {
        return NULL;
    }
    return election->tribes;
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

int main()
{
    Entity tribe = createTribe(1, "test");
    printf("%s", getEntityName(tribe));
    setEntityId(tribe, 5);
    setEntityName(tribe, "lmao this works");
    BallotBox ballot = createBallot(tribe);
    removeBallotVotes(ballot, 50);
    destroyBallot(ballot);
    if (tribe || ballot)
        ;
    destroyEntity(tribe);
    tribe = NULL;

    Entity area = createArea(2, "area");
    printf("%s", getEntityName(area));
    setEntityId(area, 5);
    setEntityName(area, "woah");
    destroyEntity(area);
    area = NULL;

    Election el = electionCreate();
    electionDestroy(el);
    // tribe = NULL;
    return 0;
}
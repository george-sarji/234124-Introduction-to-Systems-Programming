#ifndef BALLOT_H
#define BALLOT_H

#include "entity.h"
#include "ballotbox.h"

typedef struct areaBallot_t
{
    struct entity_t *area;
    struct ballotBox_t *boxes;
    struct areaBallot_t *next;
} * AreaBallot;

AreaBallot createAreaBallot(Entity area);
void destroyAreaBallot(AreaBallot ballot);
void destroyAreaBallots(AreaBallot ballot);

EntityType getBallotArea(AreaBallot ballot);
CallResult setBallotArea(AreaBallot ballot);

BallotBox getAreaBallotBoxes(AreaBallot ballot);
CallResult setAreaBallotBoxes(AreaBallot ballot);
CallResult addAreaBallotBox(AreaBallot ballot, BallotBox box);
CallResult removeAreaBallotBox(AreaBallot ballot, BallotBox box);
AreaBallot getNextAreaBallot(AreaBallot ballot);
CallResult setNextAreaBallot(AreaBallot ballot, AreaBallot next);

void destroyAreaBallot(AreaBallot ballot)
{
    if (ballot == NULL)
    {
        return;
    }
    ballot->area = NULL;
    destroyBallots(getAreaBallotBoxes(ballot));
    ballot->boxes = NULL;
    free(ballot);
    ballot = NULL;
}

void destroyAreaBallots(AreaBallot ballot)
{
    if (ballot == NULL)
    {
        return;
    }
    AreaBallot current = ballot;
    while (current != NULL)
    {
        AreaBallot next = ballot->next;
        destroyAreaBallot(current);
        current = next;
    }
}

AreaBallot getNextAreaBallot(AreaBallot ballot)
{
    if (ballot == NULL)
    {
        return NULL;
    }
    return ballot->next;
}

BallotBox getAreaBallotBoxes(AreaBallot ballot)
{
    if (ballot == NULL)
    {
        return NULL;
    }
    return ballot->boxes;
}
#endif
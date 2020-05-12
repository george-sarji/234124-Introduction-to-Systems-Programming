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

// * Declarations
// ! Create/Destroy
AreaBallot createAreaBallot(Entity area, Entity tribes);
void destroyAreaBallot(AreaBallot ballot);
void destroyAreaBallots(AreaBallot ballot);
CallResult addAreaBallotBox(AreaBallot ballot, BallotBox box);

// ! Set/Get
Entity getBallotArea(AreaBallot ballot);
CallResult setBallotArea(AreaBallot ballot, Entity area);

BallotBox getAreaBallotBoxes(AreaBallot ballot);
CallResult setAreaBallotBoxes(AreaBallot ballot, BallotBox box);

AreaBallot getNextAreaBallot(AreaBallot ballot);
CallResult setNextAreaBallot(AreaBallot ballot, AreaBallot next);

// ! Misc
CallResult removeAreaBallotBox(AreaBallot ballot, BallotBox box);
void removeTribeBallots(AreaBallot ballot, int tribe_id);

AreaBallot createAreaBallot(Entity area, Entity tribes)
{
    if (area == NULL)
    {
        return NULL;
    }
    // Allocate new area ballot.
    AreaBallot ballot = malloc(sizeof(*ballot));
    if (ballot == NULL)
    {
        return NULL;
    }
    ballot->next = NULL;
    ballot->area = area;
    // Create the new ballot boxes for the area ballot.
    if (tribes == NULL)
    {
        ballot->boxes = NULL;
        return ballot;
    }
    else
    {
        // We have active tribes. Create the first box for the chain.
        BallotBox current_box = createBallot(tribes);
        if (current_box == NULL)
        {
            destroyAreaBallot(ballot);
            return NULL;
        }
        ballot->boxes = current_box;
        Entity current = getNextEntity(tribes);
        while (current != NULL)
        {
            // Create a new box for this tribe.
            BallotBox box = createBallot(current);
            if (box == NULL)
            {
                destroyAreaBallot(ballot);
                return NULL;
            }
            setNextBallot(current_box, box);
            current_box = getNextBallot(current_box);
            current = getNextEntity(current);
        }
        return ballot;
    }
}

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

CallResult addAreaBallotBox(AreaBallot ballot, BallotBox box)
{
    if (ballot == NULL || box == NULL)
    {
        return ASSIGN_NULL;
    }
    setNextBallot(box, getAreaBallotBoxes(ballot));
    setAreaBallotBoxes(ballot, box);
    return ASSIGN_SUCCESS;
}

Entity getBallotArea(AreaBallot ballot)
{
    if (ballot == NULL)
    {
        return NULL;
    }
    return ballot->area;
}

CallResult setBallotArea(AreaBallot ballot, Entity area)
{
    if (ballot == NULL || area == NULL)
    {
        return ASSIGN_NULL;
    }
    ballot->area = area;
    return ASSIGN_SUCCESS;
}

BallotBox getAreaBallotBoxes(AreaBallot ballot)
{
    if (ballot == NULL)
    {
        return NULL;
    }
    return ballot->boxes;
}

CallResult setAreaBallotBoxes(AreaBallot ballot, BallotBox box)
{
    if (box == NULL || ballot == NULL)
    {
        return ASSIGN_NULL;
    }
    ballot->boxes = box;
    return ASSIGN_SUCCESS;
}

AreaBallot getNextAreaBallot(AreaBallot ballot)
{
    if (ballot == NULL)
    {
        return NULL;
    }
    return ballot->next;
}

CallResult setNextAreaBallot(AreaBallot ballot, AreaBallot next)
{
    if (ballot == NULL)
    {
        return ASSIGN_NULL;
    }
    ballot->next = next;
    return ASSIGN_SUCCESS;
}

void removeTribeBallots(AreaBallot ballot, int tribe_id)
{
    if (ballot == NULL || !isLegalId(tribe_id))
    {
        return;
    }
    // Go through the ballot boxes.
    AreaBallot current = ballot;
    while (current != NULL)
    {
        // Remove the tribe ballots.
        BallotBox new_chain = removeTribeBallot(getAreaBallotBoxes(current), tribe_id);
        if (new_chain == NULL)
        {
            return;
        }
        setAreaBallotBoxes(current, new_chain);
        current = getNextAreaBallot(current);
    }
}

#endif
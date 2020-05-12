
#include "entity.h"
#include "ballotbox.h"
#include "ballot.h"

AreaBallot createAreaBallot(Entity area, Entity tribes)
{
    if (area == NULL)
    {
        return NULL;
    }
    // Allocate new area ballot
    AreaBallot ballot = malloc(sizeof(*ballot));
    if (ballot == NULL)
    {
        return NULL;
    }
    ballot->area = area;
    ballot->boxes = NULL;
    ballot->next = NULL;

    // Go through the tribes.
    BallotBox box = NULL, current = box;
    while (tribes != NULL)
    {
        BallotBox new_box = createBallot(tribes);
        if (new_box == NULL)
        {
            // Destroy the area ballot.
            destroyAreaBallots(ballot);
            destroyBallots(box);
            box = NULL;
            ballot = NULL;
            return NULL;
        }
        if (box == NULL)
        {
            // First box.
            box = new_box;
            current = new_box;
        }
        else
        {
            setNextBallot(current, new_box);
            current = getNextBallot(current);
        }
        tribes = getNextEntity(tribes);
    }
    ballot->boxes = box;
    return ballot;
}

void destroyAreaBallot(AreaBallot ballot)
{
    if (ballot == NULL)
    {
        return;
    }
    ballot->area = NULL;
    destroyBallots(ballot->boxes);
    ballot->boxes = NULL;
    ballot->next = NULL;
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
        AreaBallot next = getNextAreaBallot(current);
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
    // Get the current boxes.
    BallotBox current = getAreaBallotBoxes(ballot);
    // Is this the first box we add?
    if (current == NULL)
    {
        // Set the ballot's boxes.
        setAreaBallotBoxes(ballot, box);
    }
    else
    {
        // Insert it at the front.
        setNextBallot(box, current);
        setAreaBallotBoxes(ballot, box);
    }
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
    if (ballot == NULL)
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
        BallotBox new_chain = NULL;
        CallResult result = removeTribeBallot(getAreaBallotBoxes(current), tribe_id, &new_chain);
        if (result == ASSIGN_NULL)
        {
            return;
        }
        setAreaBallotBoxes(current, new_chain);
        current = getNextAreaBallot(current);
    }
}

void insertAreaBallot(AreaBallot ballot, AreaBallot add)
{
    if (ballot == NULL || add == NULL)
    {
        return;
    }
    while (ballot != NULL)
    {
        if (getNextAreaBallot(ballot) == NULL)
        {
            setNextAreaBallot(ballot, add);
            return;
        }
        ballot = getNextAreaBallot(ballot);
    }
}

CallResult addTribeBoxes(AreaBallot ballot, Entity tribe)
{
    if (ballot == NULL)
    {
        return ASSIGN_NULL;
    }
    // Iterate through the ballots.
    AreaBallot current = ballot;
    while (current != NULL)
    {
        BallotBox box = createBallot(tribe);
        if (box == NULL)
        {
            return ASSIGN_MEMORY;
        }
        addAreaBallotBox(current, box);
        current = getNextAreaBallot(current);
    }
    return ELECTION_SUCCESS;
}

int getWinningTribe(AreaBallot ballot)
{
    if (ballot == NULL)
    {
        return -1;
    }
    BallotBox box = getAreaBallotBoxes(ballot);
    if (box == NULL)
    {
        return -1;
    }
    // Take the max as first.
    int max_votes = getBallotVotes(box), max_id = getEntityId(getBallotTribe(box));
    box = getNextBallot(box);
    while (box != NULL)
    {
        int tribe_id = getEntityId(getBallotTribe(box));
        int votes = getBallotVotes(box);
        if ((max_votes == votes && max_id > tribe_id) || max_votes < votes)
        {
            max_votes = votes;
            max_id = tribe_id;
        }
        box = getNextBallot(box);
    }
    return max_id;
}
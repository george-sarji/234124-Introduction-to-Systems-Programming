#ifndef BALLOTBOX_H
#define BALLOTBOX_H

#include <stdlib.h>
#include <stdbool.h>
#include "entity.h"
#include "ballot.h"
typedef enum voteResult_t
{
    VOTE_NULL,
    VOTE_SUCCESS,
    VOTE_ERROR
} VoteResult;

typedef struct ballotBox_t
{
    int votes;
    struct entity_t *tribe;
    struct ballotBox_t *next;
} * BallotBox;

// * Declarations
// ! CREATE/DESTROY
BallotBox createBallot(Entity tribe);
void destroyBallot(BallotBox box);
void destroyBallots(BallotBox box);

// ! GET
Entity getBallotTribe(BallotBox box);
BallotBox getNextBallot(BallotBox box);
int getBallotVotes(BallotBox box);
BallotBox getTribeBallotBox(BallotBox box, int tribe);

// ! SET
void setBallotTribe(BallotBox box, Entity tribe);
void setNextBallot(BallotBox box, BallotBox next);
void setBallotVotes(BallotBox box, int votes);

// ! MISC
ElectionResult addBallotVotes(BallotBox box, int votes);
ElectionResult removeBallotVotes(BallotBox box, int votes);
BallotBox removeTribeBallot(BallotBox box, int id);
bool isSameBallot(BallotBox box1, BallotBox box2);

// * Logic
BallotBox createBallot(Entity tribe)
{
    if (tribe == NULL)
    {
        return NULL;
    }
    BallotBox box = malloc(sizeof(*box));
    if (box == NULL)
    {
        return NULL;
    }
    box->tribe = tribe;
    box->votes = 0;
    box->next = NULL;
    return box;
}

void destroyBallot(BallotBox box)
{
    if (box == NULL)
    {
        return;
    }
    box->tribe = NULL;
    box->next = NULL;
    free(box);
    box = NULL;
}

void destroyBallots(BallotBox box)
{
    if (box == NULL)
    {
        return;
    }
    BallotBox current = box;
    while (current != NULL)
    {
        BallotBox next = getNextBallot(current);
        destroyBallot(current);
        current = next;
    }
}

Entity getBallotTribe(BallotBox box)
{
    if (box == NULL)
    {
        return NULL;
    }
    return box->tribe;
}

BallotBox getNextBallot(BallotBox box)
{
    if (box == NULL)
    {
        return NULL;
    }
    return box->next;
}

int getBallotVotes(BallotBox box)
{
    if (box == NULL)
    {
        return -1;
    }
    return box->votes;
}

BallotBox getTribeBallotBox(BallotBox box, int tribe)
{
    if (box == NULL || !isLegalId(tribe))
    {
        return NULL;
    }
    BallotBox current = box;
    while (current != NULL)
    {
        if (isSameEntityId(getBallotTribe(current), tribe))
        {
            return current;
        }
        current = getNextBallot(current);
    }
    return NULL;
}

void setBallotTribe(BallotBox box, Entity tribe)
{
    if (box == NULL || tribe == NULL)
    {
        return;
    }
    box->tribe = tribe;
}

void setNextBallot(BallotBox box, BallotBox next)
{
    if (box == NULL)
    {
        return;
    }
    box->next = next;
}

void setBallotVotes(BallotBox box, int votes)
{
    if (box == NULL || votes < 0)
    {
        return;
    }
    box->votes = votes;
    if (box->votes < 0)
    {
        box->votes = 0;
    }
}

ElectionResult addBallotVotes(BallotBox box, int votes)
{
    if (box == NULL || votes < 0)
    {
        return ELECTION_NULL_ARGUMENT;
    }
    setBallotVotes(box, getBallotVotes(box) + votes);
    return ELECTION_SUCCESS;
}

ElectionResult removeBallotVotes(BallotBox box, int votes)
{
    if (box == NULL || votes < 0)
    {
        return ELECTION_NULL_ARGUMENT;
    }
    setBallotVotes(box, getBallotVotes(box) - votes);
    return ELECTION_SUCCESS;
}

BallotBox removeTribeBallot(BallotBox box, int id)
{
    if (box == NULL || !isLegalId(id))
    {
        return NULL;
    }
    // Go through the ballots.
    // Is the first box the one we are looking for?
    if (box != NULL && isSameEntityId(getBallotTribe(box), id))
    {
        // We found the box to remove.
        BallotBox next = getNextBallot(box);
        // Destroy box and return.
        destroyBallot(box);
        return next;
    }
    // Get the previous pointer, advance current by one.
    BallotBox current = box;
    BallotBox previous = current;
    current = getNextBallot(current);
    while (current != NULL)
    {
        if (isSameEntityId(getBallotTribe(current), id))
        {
            // Remove this one.
            setNextBallot(previous, getNextBallot(current));
            destroyBallot(current);
            return box;
        }
        previous = current;
        current = getNextBallot(current);
    }
    return NULL;
}

bool isSameBallot(BallotBox box1, BallotBox box2)
{
    if (box1 == NULL || box2 == NULL)
    {
        return false;
    }
    return &box1 == &box2;
}

#endif
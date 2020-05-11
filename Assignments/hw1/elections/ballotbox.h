#ifndef BALLOTBOX_H
#define BALLOTBOX_H

#include "tribe.h"
#include <stdlib.h>

typedef enum voteResult_t
{
    VOTE_NULL,
    VOTE_SUCCESS,
    VOTE_ERROR
} VoteResult;

typedef struct ballotBox_t
{
    int votes;
    struct tribe_t *tribe;
    struct ballotBox_t *next;
} * BallotBox;

BallotBox createBallot(Tribe tribe);
void destroyBallot(BallotBox ballot);
CallResult setBallotTribe(BallotBox ballot, Tribe tribe);
CallResult setBallotNext(BallotBox ballot, BallotBox next);
BallotBox getBallotNext(BallotBox ballot);
Tribe getBallotTribe(BallotBox ballot);
VoteResult addBallotVotes(BallotBox ballot, int votes);
VoteResult removeBallotVotes(BallotBox ballot, int votes);

VoteResult removeBallotVotes(BallotBox ballot, int votes)
{
    if (ballot == NULL)
    {
        return VOTE_NULL;
    }
    ballot->votes -= votes;
    return VOTE_SUCCESS;
}

VoteResult addBallotVotes(BallotBox ballot, int votes)
{
    if (ballot == NULL)
    {
        return VOTE_NULL;
    }
    ballot->votes += votes;
    return VOTE_SUCCESS;
}

Tribe getBallotTribe(BallotBox ballot)
{
    if (ballot == NULL)
    {
        return NULL;
    }
    return ballot->tribe;
}
BallotBox getBallotNext(BallotBox ballot)
{
    if (ballot == NULL)
    {
        return NULL;
    }
    return ballot->next;
}

BallotBox createBallot(Tribe tribe)
{
    if (tribe == NULL)
    {
        return NULL;
    }
    // Allocate a ballot.
    BallotBox ballot = malloc(sizeof(*ballot));
    if (ballot == NULL)
    {
        // Return null.
        return NULL;
    }
    ballot->votes = 0;
    ballot->next = NULL;
    if (setBallotTribe(ballot, tribe) != ASSIGN_SUCCESS)
    {
        // Free everything.
        destroyBallot(ballot);
        return NULL;
    }
    return ballot;
}

void destroyBallot(BallotBox ballot)
{
    if (ballot == NULL)
    {
        return;
    }
    ballot->tribe = NULL;
    ballot->next = NULL;
    free(ballot);
    return;
}

CallResult setBallotTribe(BallotBox ballot, Tribe tribe)
{
    if (ballot == NULL || tribe == NULL)
    {
        return ASSIGN_NULL;
    }
    ballot->tribe = tribe;
    return ASSIGN_SUCCESS;
}

CallResult setBallotNext(BallotBox ballot, BallotBox next)
{
    if (ballot == NULL || next == NULL)
    {
        return ASSIGN_NULL;
    }
    ballot->next = next;
    return ASSIGN_SUCCESS;
}

#endif
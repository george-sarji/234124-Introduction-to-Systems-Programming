#ifndef BALLOTBOX_H
#define BALLOTBOX_H

#include "entity.h"
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
    struct entity_t *entity;
    struct ballotBox_t *next;
} * BallotBox;

BallotBox createBallot(Entity entity);
void destroyBallot(BallotBox ballot);
CallResult setBallotEntity(BallotBox ballot, Entity entity);
CallResult setBallotNext(BallotBox ballot, BallotBox next);
BallotBox getBallotNext(BallotBox ballot);
Entity getBallotEntity(BallotBox ballot);
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

Entity getBallotEntity(BallotBox ballot)
{
    if (ballot == NULL)
    {
        return NULL;
    }
    return ballot->entity;
}
BallotBox getBallotNext(BallotBox ballot)
{
    if (ballot == NULL)
    {
        return NULL;
    }
    return ballot->next;
}

BallotBox createBallot(Entity entity)
{
    if (entity == NULL)
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
    if (setBallotEntity(ballot, entity) != ASSIGN_SUCCESS)
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
    ballot->entity = NULL;
    ballot->next = NULL;
    free(ballot);
    return;
}

CallResult setBallotEntity(BallotBox ballot, Entity entity)
{
    if (ballot == NULL || entity == NULL)
    {
        return ASSIGN_NULL;
    }
    ballot->entity = entity;
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
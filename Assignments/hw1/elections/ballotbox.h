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
void destroyBallots(BallotBox ballot);
CallResult setBallotEntity(BallotBox ballot, Entity entity);
CallResult setBallotNext(BallotBox ballot, BallotBox next);
BallotBox getBallotNext(BallotBox ballot);
Entity getBallotEntity(BallotBox ballot);
VoteResult addBallotVotes(BallotBox ballot, int votes);
VoteResult removeBallotVotes(BallotBox ballot, int votes);
bool isSameBallot(BallotBox box1, BallotBox box2);

bool isSameBallot(BallotBox box1, BallotBox box2)
{
    return box1 != NULL && box2 != NULL && getBallotEntity(box1) != NULL && getBallotEntity(box2) != NULL && isEntityIdentical(getBallotEntity(box1), getBallotEntity(box2));
}

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

void destroyBallots(BallotBox ballot)
{
    if (ballot == NULL)
    {
        return;
    }
    BallotBox current = ballot;
    while (current != NULL)
    {
        BallotBox next = getBallotNext(ballot);
        destroyBallot(current);
        current = next;
    }
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
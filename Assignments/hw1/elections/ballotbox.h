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
CallResult removeTribeBallot(BallotBox box, int id, BallotBox *ptr);
bool isSameBallot(BallotBox box1, BallotBox box2);

#endif
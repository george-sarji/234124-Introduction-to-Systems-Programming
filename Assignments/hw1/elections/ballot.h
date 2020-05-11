#ifndef BALLOT_H
#define BALLOT_H

#include "tribe.h"

typedef struct ballotBox_t
{
    int votes;
    struct tribe_t *tribe;
    struct ballotBox_t *next;
} * BallotBox;

typedef struct areaBallot_t
{
    struct area_t *area;
    struct ballotBox_t *boxes;
} * AreaBallot;

#endif
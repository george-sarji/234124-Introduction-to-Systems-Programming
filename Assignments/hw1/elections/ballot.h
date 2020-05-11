#ifndef BALLOT_H
#define BALLOT_H

#include "area.h"

typedef struct areaBallot_t
{
    struct entity_t *area;
    struct ballotBox_t *boxes;
} * AreaBallot;

#endif
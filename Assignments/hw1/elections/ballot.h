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
int getWinningTribe(AreaBallot ballot);

// ! Misc
CallResult removeAreaBallotBox(AreaBallot ballot, BallotBox box);
void removeTribeBallots(AreaBallot ballot, int tribe_id);
CallResult addTribeBoxes(AreaBallot ballot, Entity tribe);
void insertAreaBallot(AreaBallot ballot, AreaBallot add);

#endif
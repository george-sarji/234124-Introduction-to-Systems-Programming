#include "area.h"
#include "call_result.h"
#include "tribe.h"
#include "election.h"
#include "ballot.h"
#include "ballotbox.h"
#include <stdio.h>
#include <stdlib.h>

struct election_t
{
    struct area_t *areas;
    struct tribe_t *tribes;
    struct areaBallot_t *area_ballots;
};

int main()
{
    Tribe tribe = createTribe(1, "test");
    printf("%s", getTribeName(tribe));
    setTribeId(tribe, 5);
    setTribeName(tribe, "lmao this works");  
    BallotBox ballot = createBallot(tribe);
    removeBallotVotes(ballot, 50);
    destroyBallot(ballot);
    if(tribe || ballot);
    destroyTribe(tribe);
    tribe = NULL;

    Area area = createArea(2, "area");
    printf("%s", getAreaName(area));
    setAreaId(area, 5);
    setAreaName(area, "woah");
    destroyArea(area);
    area = NULL;
    // tribe = NULL;
    return 0;
}
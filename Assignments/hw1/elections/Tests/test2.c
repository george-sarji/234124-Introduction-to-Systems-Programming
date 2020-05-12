#include <stdlib.h>
#include "../election.h"
#include <assert.h>
#include "test_utilities.h"
#include "utils.h"

int main()
{
    Election election = electionCreate();
    assert(election != NULL);
    assert(electionAddTribe(election, 11, "tribe a") == ELECTION_SUCCESS);
    assert(electionAddTribe(election, 12, "tribe b") == ELECTION_SUCCESS);
    assert(electionAddTribe(election, 13, "tribe c") == ELECTION_SUCCESS);
    assert(electionAddTribe(election, 14, "tribe d") == ELECTION_SUCCESS);
    assert(electionAddTribe(election, 15, "tribe e") == ELECTION_SUCCESS);
    assert(electionAddArea(election, 21, "area a") == ELECTION_SUCCESS);
    assert(electionAddArea(election, 22, "area b") == ELECTION_SUCCESS);
    assert(electionAddArea(election, 23, "area c") == ELECTION_SUCCESS);
    assert(electionAddArea(election, 24, "area d") == ELECTION_SUCCESS);
    assert(electionAddArea(election, 25, "area e") == ELECTION_SUCCESS);
    assert(electionAddArea(election, 26, "area f") == ELECTION_SUCCESS);
    assert(electionRemoveTribe(election, 1) == ELECTION_TRIBE_NOT_EXIST);
    electionRemoveTribe(election, 11);
    electionRemoveTribe(election, 12);
    electionRemoveTribe(election, 13);
    electionRemoveTribe(election, 14);
    electionRemoveTribe(election, 15);
    Map results = electionComputeAreasToTribesMapping(election);
    ASSERT_TEST(results);
    ASSERT_TEST(mapGetSize(results) == 0);
    mapDestroy(results);
    electionDestroy(election);
    // free(tribe_name);
    return 0;
}
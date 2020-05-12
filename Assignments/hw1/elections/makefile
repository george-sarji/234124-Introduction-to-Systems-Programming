CC = gcc
OBJS = election.o entity.o util.o map.o ballot.o ballotbox.o electionTestsExample.o node.o
EXEC = election
DEBUG_FLAG = 
COMP_FLAG =-std=c99 -Wall -Werror -pedantic-errors
RELEASE_FLAG = -DNDEBUG

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@
election.o: election.h election.c entity.h entity.c util.h util.c mtm_map/map.h mtm_map/map.c ballot.h ballot.c ballotbox.h ballotbox.c call_result.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
entity.o: call_result.h election.h election.c util.h util.c entity.c entity.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
util.o: util.h util.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
map.o: mtm_map/map.h mtm_map/map.c mtm_map/node.h mtm_map/node.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $ mtm_map/*.c
node.o: mtm_map/node.h mtm_map/node.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $ mtm_map/*.c
ballot.o: entity.h entity.c ballotbox.h ballotbox.c ballot.h ballot.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
ballotbox.o: entity.h entity.c ballot.h ballotbox.h ballotbox.c ballot.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
electionTestsExample.o: election.h test_utilities.h election.c tests/electionTestsExample.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) tests/$*.c

clean:
	rm -f $(OBJS) $(EXEC)
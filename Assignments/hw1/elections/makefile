CC = gcc
OBJS = election.o entity.o util.o map.o ballot.o ballotbox.o call_result.o
EXEC = election
DEBUG_FLAG = 
COMP_FLAG =-std=c99 -Wall -Werror -pedantic-errors
RELEASE_FLAG = -DNDEBUG

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@
election.o: election.h election.c entity.h util.h mtm_map/map.h mtm_map/map.c ballot.h ballotbox.h call_result.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
entity.o: call_result.h election.h election.c util.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
call_result.o: call_result.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
util.o: util.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
map.o: mtm_map/map.h mtm_map/map.c
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
ballot.o: entity.h ballotbox.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
ballotbox.o: entity.h ballot.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

clean:
	rm -f $(OBJS) $(EXEC)
CC = g++
OBJS = Graph.o Edge.o Vertex.o GraphException.o
EXEC = gcalc
DEBUG_FLAG = 
COMP_FLAG = -std=c++11 -Wall -Werror -pedantic-errors -fPIC
RELEASE_FLAG = -DNDEBUG

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@

Graph.o: Edge.h Edge.cpp Vertex.h Vertex.cpp GraphException.cpp GraphException.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
Vertex.o: Vertex.h Vertex.cpp GraphException.cpp GraphException.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
Edge.o: Edge.h Edge.cpp
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
GraphException.o: GraphException.cpp GraphException.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
libgraph.a: $(OBJS) 
	ar -rs $@ $^

swig:
	swig -c++ -python -o graph_wrap.c graph.i

wrapper:
	g++ -std=c++11 -DNDEBUG --pedantic-errors -Wall -Werror -I/usr/local/include/python3.6m -fPIC -shared graph_wrap.c libgraph.a -o _graph.so

tar: $(OBJS)
	zip gcalc.zip Edge.h Edge.cpp Vertex.h Vertex.cpp GraphException.cpp GraphException.h makefile Graph.cpp Graph.h Calculator.cpp

clean:
	rm -f $(OBJS) $(EXEC)
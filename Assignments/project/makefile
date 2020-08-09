CXX = /usr/local/bin/g++
OBJS = Graph.o Edge.o Vertex.o Exceptions.o Calculator.o GraphWrapper.o
EXEC = gcalc
DEBUG_FLAG = 
COMP_FLAG = -std=c++11 -Wall -Werror -pedantic-errors -fPIC
RELEASE_FLAG = -DNDEBUG

$(EXEC) : $(OBJS)
	$(CXX) $(DEBUG_FLAG) $(OBJS) -o $@

GraphWrapper.o: Graph.h Graph.cpp GraphWrapper.cpp GraphWrapper.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
Calculator.o: Edge.h Edge.cpp Vertex.h Vertex.cpp Exceptions.cpp Exceptions.h Calculator.cpp
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
Graph.o: Edge.h Edge.cpp Vertex.h Vertex.cpp Exceptions.cpp Exceptions.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
Vertex.o: Vertex.h Vertex.cpp Exceptions.cpp Exceptions.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
Edge.o: Edge.h Edge.cpp
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
Exceptions.o: Exceptions.cpp Exceptions.h
	$(CXX) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.cpp
libgraph.a: $(OBJS) 
	ar -rs $@ $^

swig:
	swig -c++ -python -o graph_wrap.c graph.i

wrapper:
	g++ -std=c++11 -DNDEBUG --pedantic-errors -Wall -Werror -I/usr/local/include/python3.6m -fPIC -shared graph_wrap.c libgraph.a -o _graph.so

tar: $(OBJS)
	zip gcalc.zip Edge.h Edge.cpp Vertex.h Vertex.cpp Exceptions.cpp Exceptions.h makefile Graph.cpp Graph.h Calculator.cpp graph.i Graph.py

clean:
	rm -f $(OBJS) $(EXEC) libgraph.a _graph.so graph_wrap.c graph_wrap.py
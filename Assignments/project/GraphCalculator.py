import graph as gw

def create():
    return gw.Graph()
def destroy(graph):
    del graph

def addVertex(graph,v):
    graph.addVertex(v)
    return graph

def addEdge(graph, v1, v2):
    graph.addEdge(v1, v2)
    return graph

def disp(graph):
    print.display(graph)

g = create()
g = addVertex(g, 'a')
# g = addEdge(g, 'a', 'b')
disp(g)
print(g)
destroy(g)
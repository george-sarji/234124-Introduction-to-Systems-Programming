import Graph

def create():
    return Graph.create()

def destroy(graph):
    return Graph.destroy(graph)

def addVertex(graph, v):
    graph.addVertex(v)
    return graph

def disp(graph):
    print(graph)

import graph as gw


def create():
    return gw.Graph()


def destroy(graph):
    graph.__del__()


def addVertex(graph, v):
    graph.addVertex(v)
    return graph


def addEdge(graph, v1, v2):
    graph.addEdge(v1, v2)
    return graph


def disp(graph):
    print(graph.toString())

def graphUnion(graph_in1, graph_in2, graph_out):
    graph_out = graph_in1 + graph_in2
    return graph_out

def graphIntersection(graph_in1, graph_in2, graph_out):
    graph_out = graph_in1 ^ graph_in2
    return graph_out

def graphDifference(graph_in1, graph_in2, graph_out):
    graph_out = graph_in1 - graph_in2
    return graph_out

def graphProduct(graph_in1, graph_in2, graph_out):
    graph_out = graph_in1 * graph_in2
    return graph_out




g = create()
g = addVertex(g, 'a')
b = create()
b = addVertex(b, 'c')
union = create()
union = g +b
print("Union: " + graphUnion(g, b, union).toString())

print("Difference: " + graphDifference(g, b, union).toString())

print("Product: " + graphProduct(g,b,union).toString())

print("Intersection: " + graphIntersection(union, g, b).toString())

destroy(g)
destroy(b)
import graph_wrap as gw


def create():
    return gw.Graph()


def destroy(graph):
    graph.__del__()
    del graph


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

# def graphComplement(graph_in, graph_out):
#     graph_out = graph_in.comp()
#     return graph_out

import graph as gw


def create():
    return gw.createGraph()


def destroy(graph):
    graph.__del__()
    del graph


def addVertex(graph, v):
    return gw.addVertex(graph, v)


def addEdge(graph, v1, v2):
    return gw.addEdge(graph, v1, v2)


def disp(graph):
    print(graph.toString())


def graphUnion(graph_in1, graph_in2, graph_out):
    return gw.graphUnion(graph_in1, graph_in2, graph_out)


def graphIntersection(graph_in1, graph_in2, graph_out):
    return gw.graphIntersection(graph_in1, graph_in2, graph_out)


def graphDifference(graph_in1, graph_in2, graph_out):
    return gw.graphDifference(graph_in1, graph_in2, graph_out)


def graphProduct(graph_in1, graph_in2, graph_out):
    return gw.graphProduct(graph_in1, graph_in2, graph_out)


def graphComplement(graph_in, graph_out):
    return gw.graphComplement(graph_in, graph_out)

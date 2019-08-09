def generate_edges(graph):
    edges = []
    for node in graph:
        for neighbour in graph[node]:
            edges.append((node, neighbour))

    return edges

def generate_vertices(graph):
    vertices = []
    for node in graph:
        vertices.append(node)

    return vertices

def find_isolated_nodes(graph):
    """ returns a list of isolated nodes. """
    isolated = []
    for node in graph:
        if not graph[node]:
            isolated += node
    return isolated

def prim(graph,w,r):
        Q=generate_vertices(graph)
        for vertice in Q:
            key[vertice]=9999999999
        key[r]=0
        pair[r]=None
        while Q:
            u=min(Q)
            Q.pop()



def main():
    graph = { "a" : ["c"],
              "b" : ["c", "e"],
              "c" : ["a", "b", "d", "e"],
              "d" : ["c"],
              "e" : ["c", "b"],
              "f" : []
            }
    print(generate_edges(graph))
    print(find_isolated_nodes(graph))
    print(generate_vertices(graph))
main()
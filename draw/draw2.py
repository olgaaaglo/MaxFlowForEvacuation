import numpy as np
import networkx as nx
import matplotlib.pyplot as plt

infinity = 1000000

#travel time, arc capacity
adj1 = [
    [[0, 0], [1, 2], [1, 2], [0, 0]],
    [[0, 0], [0, 0], [1, 2], [2, 3]],
    [[0, 0], [0, 0], [0, 0], [1, 2]],
    [[0, 0], [0, 0], [0, 0], [0, 0]],
]

#initial content, node capacity
nodes1 = [
    [3, 5], [4, 8], [3, 20], [0, infinity]
]

def FloydWarshall(graph):
	inf = 1000000
	N = len(graph)
	d = np.zeros((N, N))

	for i in range(N):
		for j in range(N):
			if i != j:
				if graph[i][j] != 0:
					d[i][j] = 1
				else:
					d[i][j] = inf

	for k in range(N):
		for i in range(N):
		    for j in range(N):
			    if d[i][k] + d[k][j] < d[i][j]:
				    d[i][j] = d[i][k] + d[k][j]
	return d

def getAdj(adjacency):
    adj = []

    for arcs in adjacency:
        line = []
        for arc in arcs:
            line.append(arc[1])
        adj.append(line)

    return np.array(adj)

# def setNodeLabels(graph):
#     nodes_labels = {}
#     for n in graph.nodes:
#         nodes_labels[n] = n + 1
#     return nx.relabel_nodes(graph, nodes_labels)

def getEdgesLabels(graph, adjacency):
    labels = nx.get_edge_attributes(graph,'weight')
    for label in labels:
        capacity = labels[label]
        labels[label] = "(" + str(adjacency[label[0]][label[1]][0]) + ", " + str(capacity) + ")"
    return labels

def getNodesPositions(pos, adj):
    distances = FloydWarshall(adj)
    s = 0
    num_nodes_same_dist = np.zeros(len(distances))
    for i in range(len(pos)):
        if distances[s][i] < 1000000:
            pos[i][0] = distances[s][i]
            num_nodes_same_dist[int(distances[s][i])] += 1

    index_nodes = np.zeros(len(distances))
    for i in range(len(pos)):
        if distances[s][i] < 1000000:
            index = int(distances[s][i])
            if num_nodes_same_dist[index] == 1:
                pos[i][1] = 0
            else:
                pos[i][1] = index_nodes[index] * 1 / (num_nodes_same_dist[index] - 1) - 0.5
                index_nodes[index] += 1
    return pos

def drawGraph(adjacency, nodes):
    adj = getAdj(adjacency)
    graph = nx.DiGraph(adj)

    # graph = setNodeLabels(graph)
    labels = getEdgesLabels(graph, adjacency)

    pos = nx.spring_layout(graph)
    pos = getNodesPositions(pos, adj)
            
    pos_attrs = {}
    for node, coords in pos.items():
        pos_attrs[node] = (coords[0], coords[1] + 0.08)

    node_attrs = {}
    for node in graph.nodes:
        node_attrs[node] = "{" + str(nodes[node][0]) + ", " + str(nodes[node][1]) + "}"


    nx.draw(graph, pos, with_labels=True, font_size=8, node_color='#a1b56c')
    nx.draw_networkx_edge_labels(graph, pos, font_size=10, edge_labels=labels)
    nx.draw_networkx_labels(graph, pos_attrs, labels=node_attrs)

    plt.draw()
    plt.savefig('../charts/graph.png')

def readAdj():
    adj = []
    with open('../input/adj.txt') as file:
        for line in file:
            splited = line.split(' ')
            vertices = [s.split(',') for s in splited]
            adj.append(vertices)
    adj = np.array(adj).astype(int).tolist()
    return adj

def readNodes():
    nodes = []
    with open('../input/nodes.txt') as file:
        for line in file:
            vertex = line.split(' ')
            nodes.append(vertex)
    nodes = np.array(nodes).astype(int).tolist()
    return nodes

def addNode0ToAdj(adj, nodes):
    adj_node0 = [[0, 0]]
    for i in range(len(nodes)):
        if nodes[i][0] != 0:
            adj_node0.append([nodes[i][0], nodes[i][1]])
        else:
            adj_node0.append([0, 0])

    adj_new = [adj_node0]
    for i in range(len(adj)):
        adj2_i = [[0, 0]] + adj[i]
        adj_new.append(adj2_i)

    return adj_new

# drawGraph(adj1, nodes1)

adj = readAdj()
nodes = readNodes()

adj = addNode0ToAdj(adj, nodes)
nodes = [[0, 0]] + nodes

drawGraph(adj, nodes)
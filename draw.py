import numpy as np
import networkx as nx
import matplotlib.pyplot as plt

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

adj = []
s = 0
t = 0
adjDone = False
with open('graph.txt') as file:
    for line in file:
        if line.strip('\n') == "---":
            adjDone = True
        elif adjDone:
            st = [int(l.strip()) for l in line.split(' ')]
            s = st[0]
            t = st[1]
        else:
            vertex = [int(l.strip()) for l in line.split(' ')]
            adj.append(vertex)
adj = np.array(adj)
distances = FloydWarshall(adj)

flow = []
with open('flow.txt') as file:
    for line in file:
        vertex = [int(l.strip()) for l in line.split(' ')]
        flow.append(vertex)
	    
graph = nx.DiGraph(adj)
labels = nx.get_edge_attributes(graph,'weight')
for label in labels:
	capacity = labels[label]
	labels[label] = str(flow[label[0]][label[1]]) + "/" + str(capacity)
	
	

pos = nx.spring_layout(graph, iterations=100)

num_nodes_same_dist = np.zeros(len(distances))
max_dist = np.max(distances[s])
for i in range(len(pos)):
	pos[i][0] = distances[s][i]
	num_nodes_same_dist[int(distances[s][i])] += 1

index_nodes = np.ones(len(distances))
for i in range(len(pos)):
	index = int(distances[s][i])
	pos[i][1] = index_nodes[index] * max_dist / num_nodes_same_dist[index]
	if i != s and i != t:
		pos[i][1] += max_dist / 2.0
	index_nodes[index] += 1


nx.draw(graph, pos, with_labels=True, font_size=8, node_color='#a1b56c')
nx.draw_networkx_edge_labels(graph, pos, font_size=10, edge_labels=labels)

plt.draw()
plt.show()

import numpy as np
import networkx as nx
import matplotlib.pyplot as plt

adj = []
with open('../out/graph.txt') as file:
    for line in file:
        vertex = [int(l.strip()) for l in line.split(' ')]
        adj.append(vertex)
adj = np.array(adj)

node_id = []
with open('../out/node_id.txt') as file:
    for line in file:
        node_id = [int(l.strip()) for l in line.split(' ')]
        break

graph = nx.DiGraph(adj)

pos = nx.spring_layout(graph)

for i in range(len(pos)):
    pos[i][0] = node_id[i] % 10
    if i == len(pos) - 1:
        pos[i][1] = - node_id[i]
    else:
        pos[i][1] = - node_id[i] / 100

node_attrs = {}
for node in graph.nodes:
    node_attrs[node] = node_id[node]

labels = nx.get_edge_attributes(graph,'weight')

nx.draw(graph, pos, font_size=8, node_color='#a1b56c')
nx.draw_networkx_edge_labels(graph, pos, font_size=10, edge_labels=labels)
nx.draw_networkx_labels(graph, pos, labels=node_attrs)

plt.draw()
plt.savefig('../charts/graph_time_expanded.png')
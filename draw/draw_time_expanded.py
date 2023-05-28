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
    if node_id[i] == 0:
        pos[i][0] = -1
    elif node_id[i] == 7:
        pos[i][0] = 3.5
    else:
        pos[i][0] = node_id[i] % 10

    if i == len(pos) - 1:
        pos[i][1] = - node_id[i]
    else:
        pos[i][1] = - node_id[i] / 100

node_attrs = {}
for node in graph.nodes:
    node_attrs[node] = node_id[node]

labels = nx.get_edge_attributes(graph,'weight')
for label in labels:
    if labels[label] == 1000000:
        labels[label] = "inf"
    print("grr ", int(node_id[label[0]] / 100), int(node_id[label[1]] / 100))
    if int(node_id[label[0]] / 100) == 4 and int(node_id[label[1]] / 100) != 6:
        labels[label] = ""

nx.draw(graph, pos, font_size=8, node_color='#a1b56c')
nx.draw_networkx_edge_labels(graph, pos, font_size=10, edge_labels=labels, bbox=dict(alpha=0))
nx.draw_networkx_labels(graph, pos, labels=node_attrs)

plt.draw()
plt.savefig('../charts/graph_time_expanded.png')
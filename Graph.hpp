#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

class Graph
{
public:
    Graph(std::vector<std::vector<int>>& cap, int s, int t) : source{s}, sink{t}
    {
        flow.resize(cap.size());
        std::fill(flow.begin(), flow.end(), std::vector<int>(cap.size(), 0));
        capacity = cap;
    }
    Graph(std::vector<std::vector<int>>& cap, int s, int t, std::vector<std::vector<int>>& dist) : source{s}, sink{t}
    {
        flow.resize(cap.size());
        std::fill(flow.begin(), flow.end(), std::vector<int>(cap.size(), 0));
        capacity = cap;
        distance = dist;
    }

    Graph(std::vector<std::vector<std::pair<int, int>>>& adj, std::vector<std::pair<int, int>>& nodes, int nr_time_intervals, int t) 
        : T{nr_time_intervals}, time_interval{t}, nrNodes{nodes.size()}
    {
        const int dynamic_net_size = nodes.size() * (T + 1) + 2;

        capacity.resize(dynamic_net_size, std::vector<int>(std::vector<int>(dynamic_net_size)));
        node_id.resize(dynamic_net_size);

        assignSourceToStartNodesArcs(nodes);
        assignArcsInside(adj, nodes, dynamic_net_size);
        assignEndNodesToSinkArcs(adj, dynamic_net_size);

        flow.resize(dynamic_net_size);
        std::fill(flow.begin(), flow.end(), std::vector<int>(dynamic_net_size, 0));
    }

    void assignSourceToStartNodesArcs(std::vector<std::pair<int, int>>& nodes)
    {
        source = 0;
        node_id[source] = 0;
        int start_node_id = 1;
        for (int i = 0; i < nodes.size(); ++i)
        {
            if (nodes[i].first > 0)
            {
                capacity[source][start_node_id] = nodes[i].first;
            }
            ++start_node_id;
        }
    }

    void assignArcsInside(std::vector<std::vector<std::pair<int, int>>>& adj, std::vector<std::pair<int, int>>& nodes, int dynamic_net_size)
    {
        int initial_node_nr = 1;
        int t = 0;
        for (int i = 1; i < dynamic_net_size; ++i)
        {
            if (i % nrNodes == 0)
            {
                ++t;
                initial_node_nr = 1;
            }
            else 
            {
                node_id[i] = initial_node_nr*10 + t;
                if (t < T)
                {
                    const auto& initial_node_nr_id = initial_node_nr - 1;
                    capacity[i][i + nrNodes] = nodes[initial_node_nr_id].second;

                    for (int j = 0; j < nrNodes; ++j)
                    {
                        if (adj[initial_node_nr_id][j].first != 0)
                        {
                            const auto& time = adj[initial_node_nr_id][j].first;
                            if (t + time <= T)
                            {
                                const auto& cap = adj[initial_node_nr_id][j].second;
                                capacity[i][i + time * nrNodes + (j - initial_node_nr_id)] = cap;
                            }
                        }
                    
                    }
                }
                ++initial_node_nr;
            }
        }
    }

    void assignEndNodesToSinkArcs(std::vector<std::vector<std::pair<int, int>>>& adj, int dynamic_net_size)
    {
        int t = 1;
        node_id[nrNodes] = nrNodes * 10;
        sink = dynamic_net_size - 1;
        for (int i = 2 * nrNodes; i <= (T + 1) * nrNodes; i += nrNodes)
        {
            node_id[i] = nrNodes * 10 + t;
            capacity[i][sink] = infinity;
            ++t;
        }
        node_id[sink] = nrNodes + 1;
    }

    void printAdjAndCapacityForNodes()
    {
        for (int i = 0; i < capacity.size(); ++i)
        {
            std::cout << "id: " << node_id[i] << std::endl;
            for (int j = 0; j < capacity.size(); ++j)
            {
                if (capacity[i][j] != 0)
                {
                    std::cout << "adj: " << j << ", id:" << node_id[j] << std::endl;
                    std::cout << "capacity: " << capacity[i][j] << std::endl;
                }

            }
            std::cout << std::endl;
        }
    }

    void printTimesForFlows()
    {
        int t = 1;
        for (int i = 2 * nrNodes; i <= (T + 1) * nrNodes; i += nrNodes)
        {
            if (flow[i][sink] != 0)
            {
                std::cout << "id: " << node_id[i] 
                    << " - " << flow[i][sink] << " people " 
                    << "evacuated in " << t * time_interval << "s" << std::endl;
                std::cout << std::endl;
            }
            ++t;
        }
    }

    void printVec(const std::vector<int>& V)
    {
        for (auto u = 0; u < V.size(); ++u)
        {
            std::cout << V[u] << " ";
        }
        std::cout << std::endl;
    }

    void printVec(const std::vector<std::vector<int>>& V)
    {
        for (auto v = 0; v < V.size(); ++v)
        {
            for (auto u = 0; u < V[v].size(); ++u)
            {
                std::cout << V[v][u] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void saveToFile()
    {
        std::ofstream file("graph.txt");

        for (auto v = 0; v < capacity.size(); ++v)
        {
            for (auto u = 0; u < capacity[v].size(); ++u)
            {
                file << capacity[v][u];
                if (u < capacity[v].size() - 1)
                {
                    file << " ";
                }
            }
            file << std::endl;
        }
        file << "---" << std::endl;
        file << source << " " << sink << std::endl;

        file.close();
    }

    void saveFlowToFile()
    {
        std::ofstream file("flow.txt");

        for (auto v = 0; v < flow.size(); ++v)
        {
            for (auto u = 0; u < flow[v].size(); ++u)
            {
                file << flow[v][u];
                if (u < flow[v].size() - 1)
                {
                    file << " ";
                }
            }
            file << std::endl;
        }

        file.close();
    }

    std::vector<std::vector<int>> flow;
    std::vector<std::vector<int>> capacity;
    std::vector<std::vector<int>> distance;
    std::vector<int> node_id;
    int source;
    int sink;
    int T;
    const int infinity{1000000};
    int time_interval;
    uint64_t nrNodes;
};
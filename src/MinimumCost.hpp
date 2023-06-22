#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
#include "Graph.hpp"
#include <deque>

constexpr int inf = 1000000;
std::ofstream file("../out/log.txt");

class MinimumCost
{
public:
    int computeMaxFlow(Graph& graph)
    {
        residualCapacity = graph.capacity;
        std::ofstream pathFile("../out/path_min_cost.txt");

        auto augmentingPath = bfs(residualCapacity, graph, pathFile);
        while (augmentingPath.size() > 0)
        {
            updateFlow(augmentingPath, graph);
            updateResidualCapacity(graph);
            
            augmentingPath = bfs(residualCapacity, graph, pathFile);
        }

        pathFile.close();
        return std::accumulate(graph.flow[graph.source].begin(), graph.flow[graph.source].end(), 0); 
    }

    int maxDynamicFlow{0};

private:
    void updateFlow(const std::deque<int>& p, Graph& graph)
    {
        auto& augmentingPathCapacity = residualCapacity[p[0]][p[1]];
        for (auto v = 1; v < p.size() - 1; ++v)
        {
            if (residualCapacity[p[v]][p[v+1]] < augmentingPathCapacity)
            {
                augmentingPathCapacity = residualCapacity[p[v]][p[v+1]];
            }
            // std::cout << "cap " << residualCapacity[p[v]][p[v+1]] << std::endl;
        }

        int chainTravelTime{0};
        for (auto v = 0; v < p.size() - 1; ++v)
        {
            if (graph.capacity[p[v]][p[v+1]] != 0)
            {
                graph.flow[p[v]][p[v+1]] += augmentingPathCapacity;
            }
            else
            {std::cout << "!!!!!" << std::endl;
                graph.flow[p[v+1]][p[v]] -= augmentingPathCapacity;
            }
            
            // std::cout << "cost " << graph.cost[p[v]][p[v+1]] << std::endl;
            chainTravelTime += graph.cost[p[v]][p[v+1]];
        }

        int repeatChain = graph.T + 1 - chainTravelTime;
        maxDynamicFlow += repeatChain * augmentingPathCapacity;
        // std::cout << "maxDynamicFlow " << augmentingPathCapacity << " " << chainTravelTime << " " << repeatChain << " " << maxDynamicFlow << std::endl;
    }

    void updateResidualCapacity(Graph& graph)
    {
        for (auto v = 0; v < graph.capacity.size(); ++v)
        {
            for (auto u = 0; u < graph.capacity.size(); ++u)
            {
                if (graph.capacity[v][u] != 0)
                {
                    residualCapacity[v][u] = graph.capacity[v][u] - graph.flow[v][u];
                }
                else if (graph.capacity[u][v] != 0)
                {
                    // residualCapacity[v][u] = graph.flow[u][v];
                }
                else
                {
                    residualCapacity[v][u] = 0;
                }
            }
        }
    }

    std::deque<int> bfs(const std::vector<std::vector<int>>& capacity, Graph& graph, std::ofstream& pathFile)
    {
        std::vector<int> parent = getParent(capacity, graph.source, graph.sink, graph.cost, graph);

        auto v = graph.sink;
        std::deque<int> p = {v};
        while (parent[v] != -1)
        {
            v = parent[v];
            p.push_front(v);
        }
        
        pathFile << "path: " << std::endl;
        for (auto u = 0; u < p.size(); ++u)
        {
            pathFile << graph.node_id[p[u]] << " ";
            if (u > 0 and graph.node_id[p[u]] % 100 < graph.node_id[p[u - 1]] % 100)
            {
                // std::cout << "<<<<<<< " << "  " << graph.node_id[p[u]] << " " << graph.node_id[p[u - 1]] << std::endl;
            }
        }
        pathFile << std::endl;
            
        return p.size() == 1 ? std::deque<int>{} : p;
    }

    std::vector<int> getParent(const std::vector<std::vector<int>>& capacity, int s, int t, const std::vector<std::vector<int>>& cost, Graph& graph)
    {
        //std::cout << "parent " << std::endl;
        std::vector<int> parent(capacity.size(), -1);
        std::vector<int> distance(capacity.size(), inf);
        std::vector<bool> visited(capacity.size(), false);
        distance[s] = 0;

        std::queue<int> queue;
        queue.push(s);

        while (not queue.empty())
        {
            int v = queue.front();
            queue.pop();
            visited[v] = false;
            if (v == t)
                break;
            for (int u = 0; u < capacity.size(); ++u)
            {
                if (capacity[v][u] > 0)
                    file << "while " << v << " " << u << " " << distance[u] << " " << distance[v] << " " << cost[v][u] << " "
                        << graph.node_id[v] << " " << graph.node_id[u] << std::endl;
                if (capacity[v][u] != 0 and distance[u] > distance[v] + cost[v][u])
                {
                    distance[u] = distance[v] + cost[v][u];
                    parent[u] = v;
                    if (not visited[u]) 
                    {
                        visited[u] = true;
                        queue.push(u);
                    } 
                    // std::cout << "if " << distance[u] << " " << parent[u] << std::endl;
                }
            }
        }

        return parent;
    }

    std::vector<std::vector<int>> residualCapacity;
};

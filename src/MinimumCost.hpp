#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
#include "Graph.hpp"
#include <deque>

constexpr int inf = 1000000;

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
        }

        for (auto v = 0; v < p.size() - 1; ++v)
        {
            if (graph.capacity[p[v]][p[v+1]] != 0)
            {
                graph.flow[p[v]][p[v+1]] += augmentingPathCapacity;
            }
            else
            {
                graph.flow[p[v+1]][p[v]] -= augmentingPathCapacity;
            }
        }
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
                    residualCapacity[v][u] = graph.flow[u][v];
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
        std::vector<int> parent = getParent(capacity, graph.source, graph.sink, graph.cost);

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
        }
        pathFile << std::endl;
            
        return p.size() == 1 ? std::deque<int>{} : p;
    }

    std::vector<int> getParent(const std::vector<std::vector<int>>& capacity, int s, int t, const std::vector<std::vector<int>>& cost)
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
                // if (capacity[v][u] > 0)
                //     std::cout << "while " << v << " " << u << " " << distance[u] << " " << distance[v] << " " << cost[v][u] << std::endl;
                if (capacity[v][u] != 0 and distance[u] > distance[v] + cost[v][u])
                {
                    distance[u] = distance[v] + cost[v][u];
                    parent[u] = v;
                    if (not visited[u]) 
                    {
                        visited[u] = true;
                        queue.push(u);
                        // std::cout << "push " << std::endl;
                    } 
                    // std::cout << "if " << distance[u] << " " << parent[u] << std::endl;
                }
            }
        }

        return parent;
    }

    std::vector<std::vector<int>> residualCapacity;
};

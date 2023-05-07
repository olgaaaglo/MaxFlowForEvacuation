#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
#include "Graph.hpp"
#include <deque>

class FordFulkerson
{
public:
    int computeMaxFlow(Graph& graph)
    {
        residualCapacity = graph.capacity;
        // time.resize(graph.capacity.size());

        auto augmentingPath = bfs(residualCapacity, graph.source, graph.sink);
        while (augmentingPath.size() > 0)
        {
            updateFlow(augmentingPath, graph);
            updateResidualCapacity(graph);
            
            augmentingPath = bfs(residualCapacity, graph.source, graph.sink);
        }
        return std::accumulate(graph.flow[graph.source].begin(), graph.flow[graph.source].end(), 0); 
    }

    // void calculateTime()
    // {

    // }

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

        // int flowFromAugmentingPath = 0;
        for (auto v = 0; v < p.size() - 1; ++v)
        {
            if (graph.capacity[p[v]][p[v+1]] != 0)
            {
                graph.flow[p[v]][p[v+1]] += augmentingPathCapacity;
                // flowFromAugmentingPath = augmentingPathCapacity;
            }
            else
            {
                graph.flow[p[v+1]][p[v]] -= augmentingPathCapacity;
                // flowFromAugmentingPath = -augmentingPathCapacity;
            }
        }

        // std::cout << "path: " << std::endl;
        // int t = 0;
        // double time_sum = 0;
        // for (auto u = 0; u < p.size(); ++u)
        // {
        //     std::cout << p[u] << std::endl;
        //     if (p[u] != graph.source and p[u] != graph.sink)
        //     {
        //         int distance = graph.distance[p[u - 1]][p[u]];
        //         if (distance > 0)
        //         {
        //             if (time[p[u]] == 0)
        //             {
        //                 time_sum += distance / 2.0;
        //                 time[p[u]] = time_sum + flowFromAugmentingPath - 1;
        //             }
        //             else 
        //             {
        //                 time[p[u]] += flowFromAugmentingPath;
        //             }
                    
        //             std::cout << "time = " << time[p[u]] << std::endl;
        //         }
        //     }
        // }
        // std::cout << std::endl;
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

    std::deque<int> bfs(const std::vector<std::vector<int>>& capacity, int s, int t)
    {
        std::vector<int> parent = getParent(capacity, s, t);

        auto& v = t;
        std::deque<int> p = {v};
        while (parent[v] != -1)
        {
            v = parent[v];
            p.push_front(v);
        }
        std::cout << "p: " << std::endl;
        for (auto u = 0; u < p.size(); ++u)
        {
            std::cout << p[u] << " ";
        }
        std::cout << std::endl;
            
        return p.size() == 1 ? std::deque<int>{} : p;
    }

    std::vector<int> getParent(const std::vector<std::vector<int>>& capacity, int s, int t)
    {
        std::vector<int> parent(capacity.size(), -1);
        std::vector<int> distance(capacity.size(), 1000000000);
        distance[s] = 0;

        std::queue<int> queue;
        queue.push(s);

        while (not queue.empty())
        {
            int v = queue.front();
            queue.pop();
            if (v == t)
                break;
            for (int u = 0; u < capacity.size(); ++u)
            {
                if (capacity[v][u] != 0 and distance[u] == 1000000000)
                {
                    distance[u] = distance[v] + 1;
                    parent[u] = v;
                    queue.push(u);
                }
            }
        }

        return parent;
    }

    std::vector<std::vector<int>> residualCapacity;
    // std::vector<double> time;
};
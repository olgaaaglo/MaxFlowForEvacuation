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
    int computeMaxFlow(Graph& G, int s, int t)
    {
        residualCapacity = G.capacity;

        auto p = bfs(residualCapacity, s, t);
        while (p.size() > 0)
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
                if (G.capacity[p[v]][p[v+1]] != 0)
                {
                    G.flow[p[v]][p[v+1]] += augmentingPathCapacity;
                }
                else
                {
                    G.flow[p[v+1]][p[v]] -= augmentingPathCapacity;
                }
            }
            
            for (auto v = 0; v < G.capacity.size(); ++v)
            {
                for (auto u = 0; u < G.capacity.size(); ++u)
                {
                    if (G.capacity[v][u] != 0)
                    {
                        residualCapacity[v][u] = G.capacity[v][u] - G.flow[v][u];
                    }
                    else if (G.capacity[u][v] != 0)
                    {
                        residualCapacity[v][u] = G.flow[u][v];
                    }
                    else
                    {
                        residualCapacity[v][u] = 0;
                    }
                }
            }
            
            p = bfs(residualCapacity, s, t);
        }
        return std::accumulate(G.flow[0].begin(), G.flow[0].end(), 0); 
        
    }
private:
    bool existsAugmentingPath()
    {
        
        return false;
    }
    std::deque<int> bfs(const std::vector<std::vector<int>>& G, int s, int t)
    {
        std::vector<int> ds(G.size(), 1000000000); //distance
        std::vector<int> ps(G.size(), -1); //parent 

        ds[s] = 0;
        std::queue<int> queue;
        queue.push(s);
        while (not queue.empty())
        {
            int v = queue.front();
            queue.pop();
            if (v == t)
                break;
            for (int u = 0; u < G.size(); ++u)
            {
                if (G[v][u] != 0 and ds[u] == 1000000000)
                {
                    ds[u] = ds[v] + 1;
                    ps[u] = v;
                    queue.push(u);
                }
            }
        }

        auto& v = t;
        std::deque<int> p = {v};
        while (ps[v] != -1)
        {
            v = ps[v];
            p.push_front(v);
        }
        if (p.size() == 1)
        {
            p.clear();
        }
            
        return p;
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

    std::vector<std::vector<int>> residualCapacity;
};
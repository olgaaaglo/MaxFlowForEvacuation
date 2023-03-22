#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

class Graph
{
public:
    Graph(std::vector<std::vector<int>>& cap)
    {
        flow.resize(cap.size());
        std::fill(flow.begin(), flow.end(), std::vector<int>(cap.size(), 0));
        capacity = cap;
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
    
    std::vector<std::vector<int>> flow;
    std::vector<std::vector<int>> capacity;  
};
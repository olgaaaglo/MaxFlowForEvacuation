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

    std::vector<std::vector<int>> flow;
    std::vector<std::vector<int>> capacity;
private:
    
};
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

    Graph(std::vector<std::vector<std::pair<int, int>>> adj, std::vector<std::pair<int, int>> nodes, int T)
    {

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
    int source;
    int sink;
    int T;
    const int infinity{1000000};
};
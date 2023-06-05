#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <numeric>
#include "Graph.hpp"
#include <deque>

std::ofstream file2("../out/log.txt");

class MonteCarlo
{
public:
    int computeMaxFlow(Graph& graph)
    {
        residualCapacity = graph.capacity;
        std::ofstream pathFile("../out/path.txt");

        auto augmentingPath = bfs(residualCapacity, graph.source, graph.sink, graph.node_id, pathFile);
        while (augmentingPath.size() > 0)
        {
            updateFlow(augmentingPath, graph);
            updateResidualCapacity(graph);
            
            augmentingPath = bfs(residualCapacity, graph.source, graph.sink, graph.node_id, pathFile);
        }

        pathFile.close();
        return std::accumulate(graph.flow[graph.source].begin(), graph.flow[graph.source].end(), 0); 
    }

private:
    void updateFlow(const std::deque<int>& p, Graph& graph)
    {
        // const auto augmentingPathCapacity = 1;
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
            {std::cout << "!!!!!" << std::endl;
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
                    // file2 << graph.node_id[v] << " " << graph.node_id[u] << " " << graph.capacity[v][u] << " " << graph.flow[v][u] << std::endl;
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
        // file2 << std::endl;
    }

    std::deque<int> bfs(const std::vector<std::vector<int>>& capacity, int s, int t, const std::vector<int>& node_id, std::ofstream& pathFile)
    {
        std::vector<int> parent = getParent(capacity, s, t, node_id);

        auto& v = t;
        std::deque<int> p = {v};
        while (parent[v] != -1)
        {
            v = parent[v];
            p.push_front(v);
        }
        
        pathFile << "path: " << std::endl;
        for (auto u = 0; u < p.size(); ++u)
        {
            pathFile << node_id[p[u]] << " ";
            // if (u < p.size() - 1)
            //     pathFile << capacity[p[u]][p[u + 1]] << " ";
            if (u > 0 and node_id[p[u]] % 100 < node_id[p[u - 1]] % 100)
            {
                std::cout << "<<<<<<< " << "  " << node_id[p[u]] << " " << node_id[p[u - 1]] << std::endl;
            }
        }
        pathFile << std::endl;
            
        return p.size() == 1 ? std::deque<int>{} : p;
    }

    std::vector<int> getParent(const std::vector<std::vector<int>>& capacity, int s, int t, const std::vector<int>& node_id)
    {
        file2 << "getParent" << std::endl;
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
            std::vector<int> possibleNextNodes;
            for (int u = 0; u < capacity.size(); ++u)
            {
                file2 << "before " << node_id[v] << " " << node_id[u] << " " << capacity[v][u] << std::endl;
                if (capacity[v][u] != 0 and distance[u] == 1000000000) //and node_id[u] / 100 != node_id[parent[v]] / 100
                {
                    possibleNextNodes.push_back(u);
                    file2 << "while " << node_id[v] << " " << node_id[u] << " " << distance[u] << " " << distance[v] << " " << node_id[parent[v]] << std::endl;
                }
                // if (capacity[v][u] != 0 and distance[u] == 1000000000)
                // {
                //     distance[u] = distance[v] + 1;
                //     parent[u] = v;
                //     queue.push(u);
                //     // std::cout << "if " << distance[u] << " " << parent[u] << std::endl;
                // }
            }
            if (possibleNextNodes.size() > 0)
            {
                const auto idx = std::rand() % possibleNextNodes.size();
                const auto nextNode = possibleNextNodes[idx];
                distance[nextNode] = distance[v] + 1;
                parent[nextNode] = v;
                queue.push(nextNode);
                possibleNextNodes.clear();
            }
        }
        return parent;
    }

    std::vector<std::vector<int>> residualCapacity;
};
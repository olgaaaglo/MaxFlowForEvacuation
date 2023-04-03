#include <iostream>
#include "Graph.hpp"
#include "FordFulkerson.hpp"

int main()
{
    std::vector<std::vector<std::vector<int>>> adjs = {
        {{ 0, 5, 4, 0 },
        { 0, 0, 6, 1 },
        { 0, 0, 0, 3 },
        { 0, 0, 0, 0 }},
        {{ 0, 5, 6, 8, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 2, 0, 0, 0 },
        { 0, 5, 0, 0, 0, 4, 0, 0 },
        { 0, 0, 0, 0, 0, 3, 10, 0 },
        { 0, 0, 3, 0, 0, 0, 0, 6 },
        { 0, 0, 0, 0, 0, 0, 0, 7 },
        { 0, 0, 0, 0, 0, 2, 0, 8 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },},
        {{ 0, 4, 5, 3, 0 },
        { 0, 0, 0, 0, 6 },
        { 0, 3, 0, 2, 0 },
        { 0, 0, 0, 0, 6 },
        { 0, 0, 0, 0, 0 }},
        {{ 0, 0, 0, 0, 0, 0, 15, 0, 0 },
        { 0, 0, 0, 0, 0, 10, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 10, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 9 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 8 },
        { 0, 0, 0, 0, 8, 0, 6, 0, 0 },
        { 0, 0, 0, 9, 0, 6, 0, 0, 0 },
        { 15, 10, 10, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 0, 0, 0, 0, 0, 0, 6, 0, 0 },
        { 0, 0, 0, 0, 0, 2, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 10, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 9 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 8 },
        { 0, 0, 0, 0, 8, 0, 6, 0, 0 },
        { 0, 0, 0, 9, 0, 6, 0, 0, 0 },
        { 6, 2, 10, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 0, 15, 10, 10, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 15, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 10, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 10, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 6, 9, 0, 0 },
        { 0, 0, 0, 0, 6, 0, 0, 8, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 9 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 8 },
        { 0, 0, 0, 0, 0, 0, 0, 0, 0 }},
    };

    std::vector<std::vector<int>> source_sink = {
      {0, 3},
      {0, 7},
      {0, 4},
      {7, 8},
      {7, 8},
      {0, 8}
    };

    // for (int i = 0; i < adjs.size(); ++i)
    // {
    //     Graph graph(adjs[i], source_sink[i][0], source_sink[i][1]);
    //     graph.saveToFile();
    //     FordFulkerson fordFulkerson;
    //     std::cout << fordFulkerson.computeMaxFlow(graph, source_sink[i][0], source_sink[i][1]) << std::endl;
    // }

    int i = 5;
    Graph graph(adjs[i], source_sink[i][0], source_sink[i][1]);
    graph.saveToFile();
    FordFulkerson fordFulkerson;
    std::cout << fordFulkerson.computeMaxFlow(graph, source_sink[i][0], source_sink[i][1]) << std::endl;
    graph.saveFlowToFile();
}
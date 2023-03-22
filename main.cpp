#include <iostream>
#include "Graph.hpp"
#include "FordFulkerson.hpp"

int main()
{
    std::vector<std::vector<int>> c_ex = {
        { 0, 5, 4, 0 },
        { 0, 0, 6, 1 },
        { 0, 0, 0, 3 },
        { 0, 0, 0, 0 }
    };

    Graph graph(c_ex);
    FordFulkerson fordFulkerson;
    std::cout << fordFulkerson.computeMaxFlow(graph, 0, 3) << std::endl;

    std::vector<std::vector<int>> c_ex2 = {
        { 0, 5, 6, 8, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 2, 0, 0, 0 },
        { 0, 5, 0, 0, 0, 4, 0, 0 },
        { 0, 0, 0, 0, 0, 3, 10, 0 },
        { 0, 0, 3, 0, 0, 0, 0, 6 },
        { 0, 0, 0, 0, 0, 0, 0, 7 },
        { 0, 0, 0, 0, 0, 2, 0, 8 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },
    };

    Graph graph2(c_ex2);
    std::cout << fordFulkerson.computeMaxFlow(graph2, 0, 7) << std::endl;
    graph2.printVec(graph2.flow);

    std::vector<std::vector<int>> c_ex3 = {
        { 0, 4, 5, 3, 0 },
        { 0, 0, 0, 0, 6 },
        { 0, 3, 0, 2, 0 },
        { 0, 0, 0, 0, 6 },
        { 0, 0, 0, 0, 0 }
    };

    Graph graph3(c_ex3);
    std::cout << fordFulkerson.computeMaxFlow(graph3, 0, 4) << std::endl;
}
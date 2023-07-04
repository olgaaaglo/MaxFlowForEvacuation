#include <iostream>
#include "Graph.hpp"
#include "FordFulkerson.hpp"
#include "MinimumCost.hpp"
#include "AgentModel.hpp"

int main()
{
    const int infinity = 1000000;
    int t;

    int T5 = 11;

    const int nrPeopleInEachRoom5 = 10;

    //t = 5;
    // int cap2 = 4;
    //int t2 = 
    // int cap4 = 3;
    // int t4 = 4;
    // int cap16 = 5;
    // int t16 = 4;

    // t = 2;
    // T5 = 82;
    // int cap2 = 1;
    // int t2 = 1;
    // int cap4 = 1;
    // int t4 = 2;
    // int cap16 = 1;
    // int t16 = 8;

    t = 10;
    int cap2 = 9;
    int t2 = 1;
    int cap4 = 7;
    int t4 = 1;
    int cap16 = 5;
    int t16 = 2;

    std::vector<std::vector<std::pair<int, int>>> adj5(27, std::vector<std::pair<int, int>>(27));
    std::vector<std::pair<int, int>> nodes5(27);
    for (int i = 0; i < 16; ++i)
    {
        nodes5[i] = {nrPeopleInEachRoom5, 15};
        if (i < 4)
        adj5[i][i + 16] = {t2, cap2};
        else if (i < 12)
        adj5[i][i + 13] = {t2, cap2};
        else if (i < 16)
        adj5[i][i + 10] = {t2, cap2};
    }
    for (int i = 16; i < 26; ++i)
    {
        nodes5[i] = {0, 1};
        if (i != 20 and i != 25)
        {
        adj5[i][i + 1] = {t4, cap4};
        }
        if (i != 15 and i != 20)
        {
            adj5[i + 1][i] = {t4, cap4};
        }
    }
    nodes5[26] = {0, infinity};
    adj5[25][20] = {t16, cap16};
    adj5[21][16] = {t16, cap16};
    adj5[20][26] = {t2, cap2};
    adj5[16][26] = {t2, cap2};


    Graph graph5_t5(adj5, nodes5, T5, t);
    Graph& graph = graph5_t5;    
    FordFulkerson fordFulkerson;
    std::cout << "Max flow = " << fordFulkerson.computeMaxFlow(graph) << std::endl << std::endl;
    graph.getTimesForFlows();
    graph.printNrPeopleInEachExit();
    graph.saveNrPeopleInEachExitInEachTimeUnit();
}
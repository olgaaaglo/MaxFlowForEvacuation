#include <iostream>
#include "Graph.hpp"
#include "FordFulkerson.hpp"
#include "MinimumCost.hpp"
#include "AgentModel.hpp"

int main()
{
    std::ofstream file("../out/pplVsTime.txt");
    std::ofstream file2("../out/nrPeopleInEachExitForPplVsTime.txt");
    const int infinity = 1000000;
    int t = 6;

    const int T5 = 26;

    for (int nrPeopleInEachRoom5 = 1; nrPeopleInEachRoom5 <= 15; ++nrPeopleInEachRoom5)
    {
        // const int nrPeopleInEachRoom5 = 15;

        std::vector<std::vector<std::pair<int, int>>> adj5(27, std::vector<std::pair<int, int>>(27));
        std::vector<std::pair<int, int>> nodes5(27);
        for (int i = 0; i < 16; ++i)
        {
        nodes5[i] = {nrPeopleInEachRoom5, 15};
        if (i < 4)
            adj5[i][i + 16] = {1, 5};
        else if (i < 12)
            adj5[i][i + 13] = {1, 5};
        else if (i < 16)
            adj5[i][i + 10] = {1, 5};
        }
        for (int i = 16; i < 26; ++i)
        {
        nodes5[i] = {0, 1};
        if (i != 20 and i != 25)
        {
            adj5[i][i + 1] = {1, 3};
        }
        if (i != 15 and i != 20)
        {
            adj5[i + 1][i] = {1, 3};
        }
        }
        nodes5[26] = {0, infinity};
        adj5[25][20] = {3, 3};
        adj5[21][16] = {3, 3};
        adj5[20][26] = {1, 5};
        adj5[16][26] = {1, 5};

        
        Graph graph5(adj5, nodes5, T5, t);
        Graph& graph = graph5;    
        FordFulkerson fordFulkerson;

        int max_flow = fordFulkerson.computeMaxFlow(graph);
        // std::cout << "Max flow = " << max_flow << std::endl << std::endl;
        int max_time = graph.getTimesForFlows(false);
        // std::cout << "Max time= " <<  max_time << std::endl << std::endl;
        file << max_flow << " " << max_time << std::endl;

        
        std::map<std::string, int> countNrPeopleInEachExit;
        for (int i = 2 * graph.nrNodes; i <= (T5 + 1) * graph.nrNodes; i += graph.nrNodes)
        {
            for (int j = 0; j < graph.flow.size(); ++j)
            {
                if (graph.flow[j][i] != 0)
                {
                    const auto label = std::to_string(graph.node_id[j] / 100) + " - " + std::to_string(graph.node_id[i] / 100);
                    countNrPeopleInEachExit[label] += graph.flow[j][i];
                }
            }
        }
        for (const auto& [label, value] : countNrPeopleInEachExit)
        {
           file2 << value << " ";
        }
        file2 << std::endl;
    }
}
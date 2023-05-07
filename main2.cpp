#include <iostream>
#include "Graph.hpp"
#include "FordFulkerson.hpp"

int main()
{
  const int infinity = 1000000;
//   const int T = 4;
// const int t = 5;

//   std::vector<std::vector<std::pair<int, int>>> adj = {
//       {{0, 0}, {1, 2}, {1, 2}, {0, 0}},
//       {{0, 0}, {0, 0}, {1, 2}, {2, 3}},
//       {{0, 0}, {0, 0}, {0, 0}, {1, 2}},
//       {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
//   };

//   std::vector<std::pair<int, int>> nodes = {
//     {{3, 5}, {4, 8}, {3, 20}, {0, infinity}}
//   };

//   Graph graph(adj, nodes, T);
//   graph.printAdjAndCapacityForNodes();
    
//   graph.saveToFile();
//   FordFulkerson fordFulkerson;
//   std::cout << fordFulkerson.computeMaxFlow(graph) << std::endl;
//   graph.saveFlowToFile();
//   graph.printTimesForFlows();

    const int T = 7;
    const int t = 6;

    std::vector<std::vector<std::pair<int, int>>> adj = {
        {{0, 0}, {0, 0}, {0, 0}, {1, 5}, {0, 0}, {0, 0}},
        {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 5}, {0, 0}},
        {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 5}, {0, 0}},
        {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {2, 3}, {2, 6}},
        {{0, 0}, {0, 0}, {0, 0}, {2, 3}, {0, 0}, {1, 2}},
        {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}
    };

    std::vector<std::pair<int, int>> nodes = {
        {{15, 15}, {10, 15}, {10, 15}, {0, 1}, {0, 1}, {0, infinity}}
    };

    Graph graph(adj, nodes, T, t);
    graph.printAdjAndCapacityForNodes();
        
    FordFulkerson fordFulkerson;
    std::cout << fordFulkerson.computeMaxFlow(graph) << std::endl;
    graph.printTimesForFlows();
}
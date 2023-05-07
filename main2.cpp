#include <iostream>
#include "Graph.hpp"
#include "FordFulkerson.hpp"

int main()
{
  const int T = 4;
  const int infinity = 1000000;

  std::vector<std::vector<std::pair<int, int>>> adj = {
      {{0, 0}, {1, 2}, {1, 2}, {0, 0}},
      {{0, 0}, {0, 0}, {1, 2}, {2, 3}},
      {{0, 0}, {0, 0}, {0, 0}, {1, 2}},
      {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
  };

  std::vector<std::pair<int, int>> nodes = {
    {{3, 5}, {4, 8}, {3, 20}, {0, infinity}}
  };

  Graph graph(adj, nodes, T);
  graph.printAdjAndCapacityForNodes();
    
  graph.saveToFile();
  FordFulkerson fordFulkerson;
  std::cout << fordFulkerson.computeMaxFlow(graph) << std::endl;
  graph.saveFlowToFile();
  graph.printTimesForFlows();
}
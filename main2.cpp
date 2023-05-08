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

//////////////////////////////////////////////

    // const int T = 7;
    // const int t = 6;

    // std::vector<std::vector<std::pair<int, int>>> adj = {
    //     {{0, 0}, {0, 0}, {0, 0}, {1, 5}, {0, 0}, {0, 0}},
    //     {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 5}, {0, 0}},
    //     {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 5}, {0, 0}},
    //     {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {2, 3}, {2, 6}},
    //     {{0, 0}, {0, 0}, {0, 0}, {2, 3}, {0, 0}, {1, 2}},
    //     {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}
    // };

    // std::vector<std::pair<int, int>> nodes = {
    //     {{15, 15}, {10, 15}, {10, 15}, {0, 1}, {0, 1}, {0, infinity}}
    // };

    // Graph graph(adj, nodes, T, t);
    // graph.printAdjAndCapacityForNodes();
        
    // FordFulkerson fordFulkerson;
    // std::cout << fordFulkerson.computeMaxFlow(graph) << std::endl;
    // graph.printTimesForFlows();

/////////////////////////////////////////////////////////

// nrPeopleInEachRoom = 2, T = 12, time = 66s
// nrPeopleInEachRoom = 8, T = 30, time = 168s

    // const int T = 30;
    // const int t = 6;

    // const int nrPeopleInEachRoom = 8;
    // std::vector<std::vector<std::pair<int, int>>> adj(29, std::vector<std::pair<int, int>>(29));
    // std::vector<std::pair<int, int>> nodes(29);
    // for (int i = 0; i < 18; ++i)
    // {
    //   nodes[i] = {nrPeopleInEachRoom, 10};
    //   if (i < 4)
    //     adj[i][i + 18] = {1, 5};
    //   else if (i < 13)
    //     adj[i][i + 14] = {1, 5};
    //   else if (i < 18)
    //     adj[i][i + 10] = {1, 5};
    // }
    // for (int i = 18; i < 27; ++i)
    // {
    //   nodes[i] = {0, 1};
    //   if (i != 22)
    //   {
    //     adj[i][i + 1] = {1, 3};
    //     if (i < 22)
    //       adj[i + 1][i] = {1, 3};
    //   }
    // }
    // nodes[27] = {0, 1};
    // nodes[28] = {0, infinity};
    // adj[27][22] = {3, 3};
    // adj[22][28] = {1, 5}; //{2, 6}; 
    // adj[18][28] = {1, 5};

    // Graph graph(adj, nodes, T, t);
    // graph.printAdjAndCapacityForNodes();
        
    // FordFulkerson fordFulkerson;
    // std::cout << fordFulkerson.computeMaxFlow(graph) << std::endl;
    // graph.printTimesForFlows();

/////////////////////////////////////////////////////

// nrPeopleInEachRoom = 2, T = 13, time = 78s
// nrPeopleInEachRoom = 8, T = 30, time = 180s

    const int T = 30;
    const int t = 6;

    const int nrPeopleInEachRoom = 2;

    std::vector<std::vector<std::pair<int, int>>> adj2(29, std::vector<std::pair<int, int>>(29));
    std::vector<std::pair<int, int>> nodes(29);
    for (int i = 0; i < 18; ++i)
    {
      nodes[i] = {nrPeopleInEachRoom, 10};
      if (i < 2)
        adj2[i][i + 18] = {1, 5};
      else if (i < 4)
        adj2[i][i + 19] = {1, 5};
      else if (i < 11)
        adj2[i][i + 14] = {1, 5};
      else if (i < 13)
        adj2[i][i + 15] = {1, 5};
      else if (i < 18)
        adj2[i][i + 10] = {1, 5};
    }
    for (int i = 18; i < 25; ++i)
    {
      nodes[i] = {0, 1};
      if (i != 22)
      {
        adj2[i][i + 1] = {1, 3};
        if (i < 22)
          adj2[i + 1][i] = {1, 3};
      }
    }

    for (int i = 25; i <= 27; ++i)
    {
        nodes[i] = {0, 1};
    }
    nodes[28] = {0, infinity};

    adj2[26][25] = {1, 3};
    adj2[27][26] = {1, 3};
    adj2[25][20] = {3, 3};
    adj2[22][28] = {1, 5};
    adj2[18][28] = {1, 5};
    
    Graph graph(adj2, nodes, T, t);
    graph.printAdjAndCapacityForNodes();
        
    FordFulkerson fordFulkerson;
    std::cout << fordFulkerson.computeMaxFlow(graph) << std::endl;
    graph.printTimesForFlows();

}
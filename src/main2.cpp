#include <iostream>
#include "Graph.hpp"
#include "FordFulkerson.hpp"
#include "MinimumCost.hpp"

int main()
{
  const int infinity = 1000000;
  int t = 5;

/////////////////////////////////////////////

  const int T1 = 4;

  //travel time, arc capacity
  std::vector<std::vector<std::pair<int, int>>> adj1 = {
      {{0, 0}, {1, 2}, {1, 2}, {0, 0}},
      {{0, 0}, {0, 0}, {1, 2}, {2, 3}},
      {{0, 0}, {0, 0}, {0, 0}, {1, 2}},
      {{0, 0}, {0, 0}, {0, 0}, {0, 0}},
  };

  //initial content, node capacity
  std::vector<std::pair<int, int>> nodes1 = {
    {{3, 5}, {4, 8}, {3, 20}, {0, infinity}}
  };

  Graph graph1(adj1, nodes1, T1, t);

//////////////////////////////////////////////

    const int T2 = 7;
    t = 6;

    std::vector<std::vector<std::pair<int, int>>> adj2 = {
        {{0, 0}, {0, 0}, {0, 0}, {1, 5}, {0, 0}, {0, 0}},
        {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 5}, {0, 0}},
        {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {1, 5}, {0, 0}},
        {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {2, 3}, {2, 6}},
        {{0, 0}, {0, 0}, {0, 0}, {2, 3}, {0, 0}, {1, 2}},
        {{0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}, {0, 0}}
    };

    std::vector<std::pair<int, int>> nodes2 = {
        {{15, 15}, {10, 15}, {10, 15}, {0, 1}, {0, 1}, {0, infinity}}
    };

    Graph graph2(adj2, nodes2, T2, t);

/////////////////////////////////////////////////////////

// nrPeopleInEachRoom = 2, T = 12, time = 66s
// nrPeopleInEachRoom = 8, T = 30, time = 168s

    const int T3 = 30;

    const int nrPeopleInEachRoom3 = 8;

    std::vector<std::vector<std::pair<int, int>>> adj3(29, std::vector<std::pair<int, int>>(29));
    std::vector<std::pair<int, int>> nodes3(29);
    for (int i = 0; i < 18; ++i)
    {
      nodes3[i] = {nrPeopleInEachRoom3, 10};
      if (i < 4)
        adj3[i][i + 18] = {1, 5};
      else if (i < 13)
        adj3[i][i + 14] = {1, 5};
      else if (i < 18)
        adj3[i][i + 10] = {1, 5};
    }
    for (int i = 18; i < 27; ++i)
    {
      nodes3[i] = {0, 1};
      if (i != 22)
      {
        adj3[i][i + 1] = {1, 3};
        if (i < 22)
          adj3[i + 1][i] = {1, 3};
      }
    }
    nodes3[27] = {0, 1};
    nodes3[28] = {0, infinity};
    adj3[27][22] = {3, 3};
    adj3[22][28] = {1, 5};
    adj3[18][28] = {1, 5};

    Graph graph3(adj3, nodes3, T3, t);

/////////////////////////////////////////////////////

// nrPeopleInEachRoom = 2, T = 13, time = 78s
// nrPeopleInEachRoom = 8, T = 30, time = 180s

    const int T4 = 30;

    const int nrPeopleInEachRoom4 = 8;

    std::vector<std::vector<std::pair<int, int>>> adj4(29, std::vector<std::pair<int, int>>(29));
    std::vector<std::pair<int, int>> nodes4(29);
    for (int i = 0; i < 18; ++i)
    {
      nodes4[i] = {nrPeopleInEachRoom4, 10};
      if (i < 2)
        adj4[i][i + 18] = {1, 5};
      else if (i < 4)
        adj4[i][i + 19] = {1, 5};
      else if (i < 11)
        adj4[i][i + 14] = {1, 5};
      else if (i < 13)
        adj4[i][i + 15] = {1, 5};
      else if (i < 18)
        adj4[i][i + 10] = {1, 5};
    }
    for (int i = 18; i < 25; ++i)
    {
      nodes4[i] = {0, 1};
      if (i != 22)
      {
        adj4[i][i + 1] = {1, 3};
        if (i < 22)
          adj4[i + 1][i] = {1, 3};
      }
    }

    for (int i = 25; i <= 27; ++i)
    {
        nodes4[i] = {0, 1};
    }
    nodes4[28] = {0, infinity};

    adj4[26][25] = {1, 3};
    adj4[27][26] = {1, 3};
    adj4[25][20] = {3, 3};
    adj4[22][28] = {1, 5};
    adj4[18][28] = {1, 5};
    
    Graph graph4(adj4, nodes4, T4, t);

////////////////////////////////////////////////////////////

    // Graph& graph = graph2;
    // graph.saveInputToFile(adj2, nodes2);
    // graph.saveAdjAndCapacityForNodesToFile();    
    // FordFulkerson fordFulkerson;
    // std::cout << "Max flow = " << fordFulkerson.computeMaxFlow(graph) << std::endl << std::endl;
    // graph.printTimesForFlows();
    // graph.printNrPeopleInEachExit();
    // graph.saveToFile();

/////////////////////////

    Graph& graph = graph2;
    MinimumCost minimumCost;
    std::cout << "Max flow = " << minimumCost.computeMaxFlow(graph) << std::endl << std::endl;
    graph.printTimesForFlows();
    graph.printNrPeopleInEachExit();

}